#include "VideoAddedOperation.h"

namespace controller {
namespace operation {

using ::model::video::Video;
using ::model::saveable::SaveableList;

VideoAddedOperation::VideoAddedOperation(Video::sptr video, SaveableList<Video>::sptr videoList) : video(video){

}

void VideoAddedOperation::doOperation() {

}

void VideoAddedOperation::undoOperation() {

}

}  // namespace operation
}  // namespace controller