#include "FFmpegDataVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

FFmpegDataVideo::FFmpegDataVideo(QString path, QSharedPointer<QOpenGLContext> context) : FileVideo(path, context) {
    throw new NotImplementedException();
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