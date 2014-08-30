#include "VideoAddedOperation.h"
#include "FilteredVideo.h"

namespace controller {
namespace operation {

using ::model::video::Video;
using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::player::Player;

VideoAddedOperation::VideoAddedOperation(FilteredVideo::sptr video, SaveableList<FilteredVideo>::sptr videoList) : video(video), 
	videoList(videoList), index(videoList->getSize()){

}

void VideoAddedOperation::doOperation() {
	videoList->insert(index,video);
}

void VideoAddedOperation::undoOperation() {
	videoList->remove(index);
}

}  // namespace operation
}  // namespace controller