#include "FFmpegDataVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

FFmpegDataVideo::FFmpegDataVideo(QString path, QSharedPointer<QOpenGLContext> context) : FileVideo(path, context) {
    throw new NotImplementedException();
}

VideoMetadata FFmpegDataVideo::getMetadata() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr FFmpegDataVideo::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

}  // namespace video
}  // namespace model