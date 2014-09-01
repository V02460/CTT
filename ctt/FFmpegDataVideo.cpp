#include "FFmpegDataVideo.h"

#include "NotImplementedException.h"
#include "IOException.h"
#include "FFmpegException.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;
using ::exception::IOException;
using ::exception::FFmpegException;
using ::model::saveable::Saveable;

FFmpegDataVideo::FFmpegDataVideo(QString path, QSharedPointer<QOpenGLContext> context) : FileVideo(path, context) {

	//TODO das muss nur einmal gemacht werden, nicht unbedingt in jedem konstruktoraufruf, muss noch angepasst werden, grad bin ich ja nur am testen und spielen
	av_register_all();

	QByteArray rawPath = path.toLocal8Bit();
	videoFormatContext = avformat_alloc_context();

	if (avformat_open_input(&videoFormatContext, rawPath.constData(), NULL, NULL) < 0)
	{
		throw IOException("FFmpeg couldn't open the file at \"" + path + "\".");
	}

	if (avformat_find_stream_info(videoFormatContext, NULL) < 0)
	{
		throw FFmpegException("FFmpeg couldn't find stream information in the file at \"" + path + "\".");
	}

	for (unsigned int i = 0; i < videoFormatContext->nb_streams; i++)
	{
		if (videoFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStreamNr = i;
			break;
		}
	}

	if (videoStreamNr == -1)
	{
		throw FFmpegException("FFmpeg couldn't find a video stream in the file at \"" + path + "\".");
	}

	codecContext = videoFormatContext->streams[videoStreamNr]->codec;

	vCodec = avcodec_find_decoder(codecContext->codec_id);
	if (vCodec == NULL) 
	{
		throw FFmpegException("FFmpeg couldn't find the codec necessary for decoding a video stream in the file at \"" + path + "\".");
	}

	//this function isn't thread safe, apparently... does it matter?
	//it says in the comments to avcodec_open2 that the context has to be allocated, bit it is already, isn't it?
	if (avcodec_open2(codecContext, vCodec, NULL) < 0)
	{
		throw FFmpegException("FFmpeg couldn't open the codec necessary to decode a video stream in the file at \"" + path + "\".");
	}

	//TODO ztdztd find this out somehow :(
	length = 100;// videoFormatContext->duration *;
}

Saveable::SaveableType FFmpegDataVideo::saveableType() {
	return getSaveableType();
}

VideoMetadata FFmpegDataVideo::getMetadata() const {

	if (isDummy())
	{
		throw IllegalStateException("Tried to request metadata from a dummy ffmpeg video");
	}

	//Testen, das ist extrem geraten bisher!!!! duration ist glaub noch in sekunden oder sowas ähnlichem
	VideoMetadata metadata(QSize(codecContext->width, codecContext->height), 1 / av_q2d(codecContext->time_base), length);
 	return metadata;
}

model::frame::Frame::sptr FFmpegDataVideo::getFrame(unsigned int frameNumber) const {

	if (isDummy())
	{
		throw IllegalStateException("Tried to request a frame from a dummy ffmpeg video");
	}

	if (frameNumber >= getMetadata().getLength())
	{
		throw IllegalArgumentException("Tried to request the frame with the number " + QString::number(frameNumber) + " from a video having only  " + QString::number(getMetadata().getLength()) + " frames.");
	}


	AVFrame *frame;
	frame = av_frame_alloc();

	AVFrame *rgbFrame;
	rgbFrame = av_frame_alloc();

	uint8_t *buffer;
	int bufferSize;

	bufferSize = avpicture_get_size(PIX_FMT_RGB24, codecContext->width, codecContext->height);
	buffer = (uint8_t *)av_malloc(bufferSize * sizeof(uint8_t));

	avpicture_fill((AVPicture *)rgbFrame, buffer, PIX_FMT_RGB24, codecContext->width, codecContext->height);

	AVPacket packet;
	av_init_packet(&packet);
	int decodingSuccessfull;

	//TODO keine ahnung ob das tut... und was es tut... ACHTUNG, anscheinend müssen da noch irgendwelche internen buffer geflusht werden damit das tut! man wird selbst irgendwie buffern müssen denk ich
	if (avformat_seek_file(videoFormatContext, videoStreamNr, frameNumber, frameNumber, frameNumber, AVSEEK_FLAG_FRAME) < 0)
	{
		throw FFmpegException("FFmpeg couldn't find the requested frame with the number " + QString::number(frameNumber) + " in the video stream.");
	}

	if (av_read_frame(videoFormatContext, &packet) < 0)
	{
		throw FFmpegException("FFmpeg couldn't read the frame with the number " + QString::number(frameNumber) + " in the video stream .");
	}

// 	if (packet.stream_index != videoStreamNr)
// 	{
// 		//TODO somethin went wrong
// 	}

	if (avcodec_decode_video2(codecContext, frame, &decodingSuccessfull, &packet) < 0)
	{
		throw FFmpegException("FFmpeg couldn't decode the frame with the number " + QString::number(frameNumber) + " in the video stream .");
	}

	if (decodingSuccessfull == 0)
	{
		throw FFmpegException("FFmpeg couldn't decode the frame with the number " + QString::number(frameNumber) + " in the video stream .");
	}

	//TODO jdwfi the following sws stuff is for conversion to rgb ppm format, this could of course be done on the gpu to be faster, but I don't know yet what the original data looks like
	SwsContext *swsContext =
		sws_getContext
		(
		codecContext->width,
		codecContext->height,
		codecContext->pix_fmt,
		codecContext->width,
		codecContext->height,
		PIX_FMT_RGB24,
		SWS_BILINEAR,
		NULL,
		NULL,
		NULL
		);

	sws_scale
		(
		swsContext,
		(uint8_t const * const *)frame->data,
		frame->linesize,
		0,
		codecContext->height,
		rgbFrame->data,
		rgbFrame->linesize
		);

	QImage rgbImage(rgbFrame->data[0], codecContext->width, codecContext->height, QImage::Format_RGB888);

	Frame::sptr result(new Frame(context, rgbImage));

	av_free_packet(&packet);
	av_free(buffer);
	av_free(rgbFrame);
	av_free(frame);

	return result;
}

Saveable::SaveableType FFmpegDataVideo::getSaveableType() {
    return SaveableType::fFmpegDataVideo;
}

FFmpegDataVideo::~FFmpegDataVideo()
{
	//TODO useizf close the codec itself? how?
	avcodec_close(codecContext);
	avformat_close_input(&videoFormatContext);
}

void FFmpegDataVideo::restore(::model::saveable::Memento memento)
{
	throw NotImplementedException();
}

unsigned int FFmpegDataVideo::getFrameCount() const
{
	if (isDummy())
	{
		throw IllegalStateException("Tried to request the frame count of a dummy ffmpeg video");
	}
	return length;
}

::model::saveable::Memento FFmpegDataVideo::getMemento() const
{
	throw NotImplementedException();
}

}  // namespace video
}  // namespace model