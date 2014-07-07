#include "YUVDataVideo.h"

namespace model {
namespace video {

using ::model::frame::Frame;

YUVDataVideo::YUVDataVideo(QDir videoFile, QDir metadataFile, QOpenGLContext context) : FileVideo(videoFile) {

}

YUVDataVideo::~YUVDataVideo() {

}

VideoMetadata YUVDataVideo::getMetadata() const {

}

Frame YUVDataVideo::getFrame(unsigned int frameNumber) const {

}

}  // namespace video
}  // namespace model