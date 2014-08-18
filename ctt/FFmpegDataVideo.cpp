#include "FFmpegDataVideo.h"

#include "NotImplementedException.h"


namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;
using ::model::saveable::Saveable;

FFmpegDataVideo::FFmpegDataVideo(QString path, QSharedPointer<QOpenGLContext> context) : FileVideo(path, context) {
    throw new NotImplementedException();

	//TODO das muss nur einmal gemacht werden, nicht unbedingt in jedem konstruktoraufruf, muss noch angepasst werden, grad bin ich ja nur am testen und spielen
	av_register_all();

	QByteArray rawPath = path.toLocal8Bit();
	if (avformat_open_input(&videoFormatContext, rawPath.constData(), NULL, NULL) < 0)
	{
		//TODO ksfej IOException, oder FFMpeg Exception? couldn't open file
	}

	if (avformat_find_stream_info(videoFormatContext, NULL) < 0)
	{
		//TODO sjkrwgf ffmpegException no stream information found
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
		//TODO jhae exception no video stream found
	}

	codecContext = videoFormatContext->streams[videoStreamNr]->codec;

	vCodec = avcodec_find_decoder(codecContext->codec_id);
	if (vCodec == NULL) 
	{
		//TODO zusefgu exception unsupported codec
	}

	//this function isn't thread safe, apparently... does it matter?
	//it says in the comments to avcodec_open2 that the context has to be allocated, bit it is already, isn't it?
	if (avcodec_open2(codecContext, vCodec, NULL) < 0)
	{
		//TODO exception could not open codec
	}


}

VideoMetadata FFmpegDataVideo::getMetadata() const {
    throw new NotImplementedException();
	
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request metadata from a dummy ffmpeg video");
	}

	//Testen, das ist extrem geraten bisher!!!!
	VideoMetadata metadata(QSize(codecContext->width, codecContext->height), 1 / av_q2d(codecContext->time_base), videoFormatContext->duration);
// 	return metadata;
}

model::frame::Frame::sptr FFmpegDataVideo::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();

	if (isDummy())
	{
		throw new IllegalStateException("Tried to request a frame from a dummy ffmpeg video");
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
	int decodingSuccessfull;

	//TODO keine ahnung ob das tut... und was es tut... ACHTUNG, anscheinend müssen da noch irgendwelche internen buffer geflusht werden damit das tut! man wird selbst irgendwie buffern müssen denk ich
	if (avformat_seek_file(videoFormatContext, videoStreamNr, frameNumber, frameNumber, frameNumber, AVSEEK_FLAG_FRAME) < 0)
	{
		//TODO ehfga exception couldn't go to the requested frame?
	}

	if (av_read_frame(videoFormatContext, &packet) < 0)
	{
		//TODO jse exception couldn't read frame, maybe eof
	}

// 	if (packet.stream_index != videoStreamNr)
// 	{
// 		//TODO somethin went wrong
// 	}

	if (avcodec_decode_video2(codecContext, frame, &decodingSuccessfull, &packet) < 0)
	{
		//TODO ssrsgf exception decoding failed
	}

	if (decodingSuccessfull == 0)
	{
		//TODO ssrsgf exception decoding failed
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

	QByteArray rawRGBppm;
	QImage rgbImage;
	rgbImage.loadFromData(rawRGBppm);


	//TODO zaueuf get all the fancy metadata, motion vectors and stuff

	av_free_packet(&packet);
	av_free(buffer);
	av_free(rgbFrame);
	av_free(frame);
}

Saveable::SaveableType FFmpegDataVideo::getType() const {
	return Saveable::SaveableType::fFmpegDataVideo;
}

FFmpegDataVideo::~FFmpegDataVideo()
{
	//TODO useizf close the codec itself? how?
	avcodec_close(codecContext);
	avformat_close_input(&videoFormatContext);
}

}  // namespace video
}  // namespace model