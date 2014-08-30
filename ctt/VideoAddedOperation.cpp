#include "VideoAddedOperation.h"
#include "FFmpegDataVideo.h"
#include "YUVDataVideo.h"

namespace controller {
namespace operation {

using ::model::video::Video;
using ::model::saveable::SaveableList;
using ::model::video::FFmpegDataVideo;
using ::model::video::YUVDataVideo;

VideoAddedOperation::VideoAddedOperation(Video::sptr video, SaveableList<Video>::sptr videoList) : video(video), videoList(videoList), memento(video->getMemento()){

}

void VideoAddedOperation::doOperation() {
	videoList->insert(videoList->getSize(),video);
	index = (videoList->getSize()) - 1;
}

void VideoAddedOperation::undoOperation() {
	videoList->remove(index);
}

}  // namespace operation
}  // namespace controller