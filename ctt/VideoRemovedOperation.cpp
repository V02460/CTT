#include "VideoRemovedOperation.h"

namespace controller {
namespace operation {

using ::model::saveable::SaveableList;
using ::model::video::Video;

VideoRemovedOperation::VideoRemovedOperation(int index, SaveableList<Video> videoList) {

}

void VideoRemovedOperation::doOperation() {

}

void VideoRemovedOperation::undoOperation() {

}

}  // namespace operation
}  // namespace controller