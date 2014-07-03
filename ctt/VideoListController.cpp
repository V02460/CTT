#include "VideoListController.h"

namespace controller {

using ::model::SaveableList;
using ::model::video::Video;

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

}  // namespace controller