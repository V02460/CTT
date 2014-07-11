#include "VideoScrubber.h"

namespace model {
namespace player {

using ::model::video::Video;
using ::model::video::VideoMetadata;
using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;

VideoScrubber::VideoScrubber(video::Video::sptr video) : video(video) {
	//TODO throw Exception if Video is invalid... is this even possible?
	waitingForFrame = true;
	currentFrame.reset(&video->getFrame(0));
	waitingForFrame = false;
}

VideoScrubber::~VideoScrubber() {

}

VideoScrubber::VideoScrubber(video::Video::sptr video, unsigned int frameNumber) {
	//TODO throw Exception if Video is invalid... is this even possible?
	waitingForFrame = true;
	currentFrame = video->getFrame(frameNumber);
	waitingForFrame = false;
}

VideoMetadata VideoScrubber::getVideoMetadata() const {

}

Video::sptr VideoScrubber::getVideo() const {

}

Frame::sptr VideoScrubber::getCurrentFrame() const{

}

bool VideoScrubber::isWaitingForFrame() const {

}

void VideoScrubber::jumpToFrameNr(unsigned int frameNumber) {

}

Memento VideoScrubber::getMemento() const {
}

void VideoScrubber::restore(Memento memento) {
}

Saveable::sptr VideoScrubber::getDummy() {

}

}  // namespace player
}  // namespace model