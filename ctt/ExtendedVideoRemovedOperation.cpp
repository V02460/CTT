#include "ExtendedVideoRemovedOperation.h"

#include "FilteredVideo.h"

namespace controller {
namespace operation {

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::player::Player;

ExtendedVideoRemovedOperation::ExtendedVideoRemovedOperation(int index,
			                                                 SaveableList<FilteredVideo>::sptr videoList,
															 SaveableList<FilteredVideo>::sptr filteredVideos,
															 SaveableList<Player>::sptr playerList)
		: index(index),
		  videoList(videoList),
		  filteredVideos(filteredVideos),
		  playerList(playerList),
		  videoListMemento(videoList->getMemento()),
		  filteredVideosMemento(filteredVideos->getMemento()),
		  playerListMemento(playerList->getMemento()){}

void ExtendedVideoRemovedOperation::doOperation() {
	videoList->remove(index);
	filteredVideos->remove(index);
	playerList->remove(index);
}

void ExtendedVideoRemovedOperation::undoOperation() {
	videoList->restore(videoListMemento);
	filteredVideos->restore(filteredVideosMemento);
	playerList->restore(playerListMemento);
	videoList->changed();
	filteredVideos->changed();
	playerList->changed();
}

}  // namespace operation
}  // namespace controller