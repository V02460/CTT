#include "ExtendedVideoRemovedOperation.h"

#include "FilteredVideo.h"

namespace controller {
namespace operation {

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;

ExtendedVideoRemovedOperation::ExtendedVideoRemovedOperation(int index,
			                                                 SaveableList<FilteredVideo>::sptr videoList,
															 SaveableList<FilteredVideo>::sptr filteredVideos)
		: index(index),
		  videoList(videoList),
		  filteredVideos(filteredVideos),
		  videoListMemento(videoList->getMemento()),
		  filteredVideosMemento(filteredVideos->getMemento()) {}

void ExtendedVideoRemovedOperation::doOperation() {
	videoList->remove(index);
	filteredVideos->remove(index);
}

void ExtendedVideoRemovedOperation::undoOperation() {
	videoList->restore(videoListMemento);
	filteredVideos->restore(filteredVideosMemento);
	videoList->changed();
	filteredVideos->changed();
}

}  // namespace operation
}  // namespace controller