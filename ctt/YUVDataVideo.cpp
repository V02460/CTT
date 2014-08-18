#include "YUVDataVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

YUVDataVideo::YUVDataVideo(QDir videoFile, QDir metadataFile, QOpenGLContext context) : FileVideo(videoFile) {
    throw new NotImplementedException();
}

YUVDataVideo::~YUVDataVideo() {
    throw new NotImplementedException();
}

VideoMetadata YUVDataVideo::getMetadata() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr YUVDataVideo::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType YUVDataVideo::getType() const {
	return Saveable::SaveableType::yUVDataVideo;
}


}  // namespace video
}  // namespace model