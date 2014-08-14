#include "FFmpegDataVideo.h"

#include "NotImplementedException.h"

extern "C"
{
#include "dev\include\libavcodec\avcodec.h"
#include "dev\include\libavformat\avformat.h"
}

#pragma comment(lib, "dev\\lib\\avformat.lib")
#pragma comment(lib, "dev\\lib\\avcodec.lib")

namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

FFmpegDataVideo::FFmpegDataVideo(QString path, QSharedPointer<QOpenGLContext> context) : FileVideo(path, context) {
    throw new NotImplementedException();

	//TODO das muss nur einmal gemacht werden, nicht unbedingt in jedem konstruktoraufruf, muss noch angepasst werden, grad bin ich ja nur am testen und spielen
	av_register_all();


	AVFormatContext *fileInfo;

	QByteArray rawPath = path.toLocal8Bit();
	if (avformat_open_input(&fileInfo, rawPath.constData(), NULL, NULL) != 0)
	{

	}
}

VideoMetadata FFmpegDataVideo::getMetadata() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr FFmpegDataVideo::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType FFmpegDataVideo::getType() const {
	return Saveable::SaveableType::fFmpegDataVideo;
}

}  // namespace video
}  // namespace model