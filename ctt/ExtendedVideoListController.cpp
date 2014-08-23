#include "ExtendedVideoListController.h"

#include "IllegalArgumentException.h"
#include "NotImplementedException.h"


namespace controller {

	using ::model::saveable::SaveableList;
	using ::model::video::Video;
	using ::model::filter::FilteredVideo;
	using ::model::player::Player;

	ExtendedVideoListController::ExtendedVideoListController(SaveableList<Video>::sptr baseVideos,
		SaveableList<FilteredVideo>::sptr filteredVideos,
		SaveableList<Player>::sptr player) : VideoListController(baseVideos), filteredVideos(filteredVideos), player(player){
	}

	void ExtendedVideoListController::addVideo(QString path) {
		throw new exception::NotImplementedException();
	}

	void ExtendedVideoListController::addVideo(Video::sptr video) {
		videoList->insert(videoList->getSize(), video);
		FilteredVideo::sptr filteredVideo(new FilteredVideo(video));
		filteredVideos->insert(filteredVideos->getSize(), filteredVideo);
	}

	void ExtendedVideoListController::removeVideo(int index) {
		videoList->remove(index);
	}

	void ExtendedVideoListController::removeVideo(const Video &video) {
		for (int i = 0; i < videoList->getSize(); i++) {
			if (&video == videoList->get(i).data()) {
				removeVideo(i);
				return;
			}
			throw new exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
		}
	}

}  // namespace controller