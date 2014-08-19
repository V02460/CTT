#include "VideoListController.h"

#include "IllegalArgumentException.h"


namespace controller {

using ::model::saveable::SaveableList;
using ::model::video::Video;

VideoListController::VideoListController(SaveableList<Video>::sptr videoList): videoList(videoList) {

}

void VideoListController::addVideo(QString path) {
	// ACHTUNG!
	Video::sptr video;
	videoList->insert(videoList->getSize(), video);
}

void VideoListController::addVideo(Video::sptr video) {
	videoList->insert(videoList->getSize(), video);
}

void VideoListController::removeVideo(int index) {
	videoList->remove(index);
}

void VideoListController::removeVideo(const Video &video) {
	for (int i = 0; i < videoList->getSize; i++) {
		if (video == videoList[i]) {
			removeVideo(i);
			return;
		}
		throw new exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
	}
}

}  // namespace controller