#include "FFmpegDataVideo.h"

namespace model {
namespace video {

using ::model::frame::Frame;

FFmpegDataVideo::FFmpegDataVideo(QDir path, QSharedPointer<QOpenGLContext> context) {

}

VideoMetadata FFmpegDataVideo::getMetadata() const {

}

Frame FFmpegDataVideo::getFrame(unsigned int frameNumber) const {

}

}  // namespace video
}  // namespace model