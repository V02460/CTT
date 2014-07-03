#include "YUVDataVideo.h"

namespace model {
namespace video {

using ::model::frame::Frame;

YUVDataVideo::YUVDataVideo(QFile videoFile, QFile metadataFile, QOpenGLContext context) {

}

VideoMetadata YUVDataVideo::getMetadata() const {

}

Frame YUVDataVideo::getFrame(unsigned int frameNumber) const {

}

}  // namespace video
}  // namespace model