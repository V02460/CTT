#include "VideoAddedOperation.h"
#include "FilteredVideo.h"

namespace controller {
namespace operation {

using ::model::video::Video;
using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;

VideoAddedOperation::VideoAddedOperation(FilteredVideo::sptr video, SaveableList<FilteredVideo>::sptr videoList)
		: video(video),
		  videoList(videoList),
		  index(videoList->getSize()),
		  memento(videoList->getMemento()) {}

void VideoAddedOperation::doOperation() {
	videoList->insert(index,video);
}

void VideoAddedOperation::undoOperation() {
	videoList->restore(memento);
	videoList->changed();
}

}  // namespace operation
}  // namespace controller