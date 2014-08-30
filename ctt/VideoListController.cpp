#include "VideoListController.h"

#include "NotImplementedException.h"

namespace controller {

using ::model::saveable::SaveableList;
using ::model::video::Video;
using ::exception::NotImplementedException;

VideoListController::VideoListController(SaveableList<Video>::sptr videoList) {

}

void VideoListController::addVideo(QString path) {

}

void VideoListController::addVideo(Video::sptr video) {

}

void VideoListController::removeVideo(int index) {

}

void VideoListController::removeVideo(const Video &video) {

}

void VideoListController::update() {
	throw new NotImplementedException();
}

}  // namespace controller