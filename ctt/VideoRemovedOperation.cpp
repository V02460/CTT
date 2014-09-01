#include "VideoRemovedOperation.h"

#include "FilteredVideo.h"

namespace controller {
namespace operation {

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;

VideoRemovedOperation::VideoRemovedOperation(int index, SaveableList<FilteredVideo>::sptr videoList)
		: index(index),
		  videoList(videoList),
		  memento(videoList->getMemento()) {}

void VideoRemovedOperation::doOperation() {
	videoList->remove(index);
}

void VideoRemovedOperation::undoOperation() {
	videoList->restore(memento);
	videoList->changed();
}

}  // namespace operation
}  // namespace controller