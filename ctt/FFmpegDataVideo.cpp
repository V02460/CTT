#include "FFmpegDataVideo.h"

#define FFmpeg_PixelFormat PixelFormat
#undef PixelFormat

#include "GPUSurfaceShader.h"
#include "GlobalContext.h"

#include "FFmpegException.h"
#include "NotImplementedException.h"
#include "AccessToDummyException.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::model::saveable::Memento;
using ::helper::GPUSurfaceShader;
using ::model::GlobalContext;
using ::model::saveable::Saveable;
using ::exception::FFmpegException;
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;

class FFmpegPacket {
public:
    typedef QScopedPointer<FFmpegPacket> uptr;
    typedef QSharedPointer<FFmpegPacket> sptr;
    typedef QWeakPointer<FFmpegPacket> wptr;

    /**
     * Creates a FFmpegPacket and fills it with the next fitting data in the stream.
     */
    FFmpegPacket(AVFormatContext *avFormatContext, int streamNumber)
            : avFormatContext(avFormatContext)
            , streamNumber(streamNumber) {
        retrieveNewData();
    }

    ~FFmpegPacket() {
        av_free_packet(&packet);
    }

    bool retrieveNewData() {
        // get a packet from the correct stream
        while (1) {
            if (av_read_frame(avFormatContext, &packet)) {
                //throw FFmpegException("Error or end of file reached.");
                isEmptyFlag = true;
                return false;
            }

            if (packet.stream_index == streamNumber) {
                isEmptyFlag = false;
                return true;
            }

            av_free_packet(&packet);
        }
    }

    bool isEmpty() const {
        return isEmptyFlag;
    }

    AVPacket *data() {
        return &packet;
    }

private:
    Q_DISABLE_COPY(FFmpegPacket);

    AVFormatContext *avFormatContext;
    int streamNumber;

    AVPacket packet;
    bool isEmptyFlag = true;
};

class FFmpegFrame {
public:
    typedef QScopedPointer<FFmpegFrame> uptr;
    typedef QSharedPointer<FFmpegFrame> sptr;
    typedef QWeakPointer<FFmpegFrame> wptr;

    FFmpegFrame(AVFormatContext *avFormatContext, AVCodecContext *avCodecContext, int streamNr)
            : avCodecContext(avCodecContext)
            , isEmptyFlag(false) {
        frame = av_frame_alloc();
        if (!frame) {
            throw FFmpegException("Could not allocate Frame.");
        }

        int got_picture = false;

        while (!got_picture) {
            FFmpegPacket packet(avFormatContext, streamNr);
            if (packet.isEmpty()) {
                isEmptyFlag = true;
                break;
            }

            int nb_decompressedBytes = avcodec_decode_video2(avCodecContext, frame, &got_picture, packet.data());
            if (nb_decompressedBytes < 0) {
                throw FFmpegException("Failed to decode frame.");
            }
        } 
    }

    ~FFmpegFrame() {
        av_frame_free(&frame);
    }

    QSize getSize() const {
        return QSize(frame->width, frame->height);
    }

    int64_t getPTS() {
        return frame->pkt_dts;
    }

    Surface::sptr getPlaneFromRawData(QSize planeSize, unsigned char *data, int linesize) {
        unsigned char *planeBuffer;

        auto plane = Surface::sptr::create(GlobalContext::get(),
                                           planeSize,
                                           reinterpret_cast<void**>(&planeBuffer),
                                           QOpenGLTexture::UInt8,
                                           QOpenGLTexture::Red,
                                           QOpenGLTexture::R8_UNorm);

        // row by row copy from ffmpeg to gpu
        for (int i = 0; i < planeSize.height(); i++) {
            memcpy(planeBuffer + i * planeSize.width(),
                   data + i * linesize,
                   planeSize.width());
        }

        plane->finishTextureUpload();

        return plane;
    }

    Frame::sptr getGPUFrame() {
        QSize yPlaneSize = getSize();
        QSize chromaPlaneSize = yPlaneSize / 2;

        Surface::sptr yPlane = getPlaneFromRawData(yPlaneSize, frame->data[0], frame->linesize[0]);
        Surface::sptr uPlane = getPlaneFromRawData(chromaPlaneSize, frame->data[1], frame->linesize[1]);
        Surface::sptr vPlane = getPlaneFromRawData(chromaPlaneSize, frame->data[2], frame->linesize[2]);

        // convert YUV to RGB
        // TODO implement support for hdtv
        GPUSurfaceShader yuvToRGBConverter(":/Shader/Conversion/YUV420toRGBsdtv.fs", yPlane);

        yuvToRGBConverter.setValue("uChannel", uPlane);
        yuvToRGBConverter.setValue("vChannel", vPlane);
        yuvToRGBConverter.invertY(true);

        Surface::sptr rgbSurface = yuvToRGBConverter.run(yPlaneSize);

        // Add metadata to Surface to make it a Frame
        return Frame::sptr::create(rgbSurface, FrameMetadata(getSize()));
    }

    bool isEmpty() const {
        return isEmptyFlag;
    }

private:
    Q_DISABLE_COPY(FFmpegFrame);

    AVCodecContext *avCodecContext;

    AVFrame *frame;

    bool isEmptyFlag;
};


FFmpegDataVideo::FFmpegDataVideo(QString path, QSharedPointer<QOpenGLContext> context)
        : FileVideo(path, context)
        , path(path)
        ,frameCount(0) {
    init();
}

void FFmpegDataVideo::init() {
    loadVideo();

    while (!FFmpegFrame(avFormatContext, avCodecContext, bestStreamNr).isEmpty()) {
        frameCount++;
    }

    getFrame(0);
}

void FFmpegDataVideo::loadVideo() {
    // be ready to handle all formats
    av_register_all();

    // create the context for receiving stream information
    // avFormatContext = avformat_alloc_context();

    // let FFmpeg allocate the context
    avFormatContext = NULL;

    // open file
    if (avformat_open_input(&avFormatContext, path.toLatin1(), NULL, NULL) != 0) {
        throw FFmpegException("Could not open video file '" + path + "'.");
    }

    // get infos needed to find the best video stream
    int ret = avformat_find_stream_info(avFormatContext, NULL);
    if (ret < 0) {
        av_make_error_string(ffmpegErrorStr.data(), AV_ERROR_MAX_STRING_SIZE, ret);
        throw FFmpegException("Could not find stream info: " + ffmpegErrorStr);
    }

    AVCodec *codec;
    // find the best video stream
    bestStreamNr = av_find_best_stream(avFormatContext, AVMediaType::AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
    if (bestStreamNr < 0) {
        switch (bestStreamNr) {
            case AVERROR_STREAM_NOT_FOUND:
                throw FFmpegException("Given files does not contain a video stream.");
            case AVERROR_DECODER_NOT_FOUND:
                throw FFmpegException("Did not find a decoder for any video stream.");
            default:
                throw FFmpegException("Unknown error occurred when calling av_find_best_stream.");
        }
    }

    // get fps
    fps = av_q2d(av_stream_get_r_frame_rate(avFormatContext->streams[bestStreamNr]));

    avCodecContext = avcodec_alloc_context3(codec);
    if (!avCodecContext) {
        throw FFmpegException("Could not create codec context.");
    }

    if (avcodec_open2(avCodecContext, codec, NULL) != 0) {
        throw FFmpegException("Could not open codec.");
    }



    // set function to choose output pixel format
    //avCodecContext->get_format = pickPixelFormat;
}

FFmpegDataVideo::~FFmpegDataVideo() {
    if (isDummy()) {
        return;
    }

    avcodec_close(avCodecContext);
    avcodec_free_context(&avCodecContext);

    avformat_close_input(&avFormatContext);
    avformat_free_context(avFormatContext);
}

Frame::sptr FFmpegDataVideo::getFrame(unsigned int frameNumber) const {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    if (frameNumber >= getFrameCount()) {
        throw IllegalArgumentException("Requested frame number " +
                                       QString::number(frameNumber) +
                                       " from video which only has " +
                                       QString::number(getFrameCount()) +
                                       " frames.");
    }

    // do we want the last frame again?
    if (frameNumber == lastFrameNr) {
        return lastFrame;
    }

    unsigned int decodeStart = 0;

    // do we need a frame ahead?
    if (lastFrameNr != -1 && frameNumber > lastFrameNr) {
        decodeStart = lastFrameNr + 1;
    } else {
        // seek to begin
        avformat_seek_file(avFormatContext,
                           bestStreamNr,
                           0,
                           0,
                           0,
                           AVSEEK_FLAG_FRAME | AVSEEK_FLAG_ANY);
    }

    FFmpegFrame::sptr frame;

    // TODO: don't bruteforce new frame position
    for (unsigned int i = decodeStart; i <= frameNumber; i++) {
        frame = FFmpegFrame::sptr::create(avFormatContext, avCodecContext, bestStreamNr);
        if (frame->isEmpty()) { 
            throw FFmpegException("Could not read frame " + QString::number(i) + " from stream.");
        }
    }

    lastFrame = frame->getGPUFrame();
    lastFrameNr = frameNumber;

    return lastFrame;
}

const QString FFmpegDataVideo::kPathAttrStr = "path";

VideoMetadata FFmpegDataVideo::getMetadata() const {
    Frame::sptr probeFrame;

    if (lastFrame.isNull()) {
        probeFrame = getFrame(0);
    } else {
        probeFrame = lastFrame;
    }

    return VideoMetadata(probeFrame->getSize(), fps, frameCount);
}

unsigned int FFmpegDataVideo::getFrameCount() const {
    return frameCount;
}

Memento FFmpegDataVideo::getMemento() const {
    Memento memento;

    memento.setString(kPathAttrStr, path);

    return memento;
}

void FFmpegDataVideo::restore(Memento memento) {
    FileVideo::restore(memento);

    path = memento.getString(kPathAttrStr);

    init();
}

FFmpegDataVideo::FFmpegDataVideo() {
    isDummyFlag = true;
}

Saveable::sptr FFmpegDataVideo::getDummy() {
    return Saveable::sptr(new FFmpegDataVideo());
}

}  // namespace video
}  // namespace model

#define PixelFormat FFmpeg_PixelFormat
#undef FFmpeg_PixelFormat