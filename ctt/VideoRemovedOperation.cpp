#include "VideoRemovedOperation.h"

namespace controller {
namespace operation {

using ::model::saveable::SaveableList;
using ::model::video::Video;

VideoRemovedOperation::VideoRemovedOperation(int index, SaveableList<Video>::sptr videoList) : index(index), video(videoList->get(index)), videoList(videoList){

}

void VideoRemovedOperation::doOperation() {
	videoList->remove(index);
}

void VideoRemovedOperation::undoOperation() {
	videoList->insert(index, video);
}

}  // namespace operation
}  // namespace controller