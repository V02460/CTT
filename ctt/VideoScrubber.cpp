#include "VideoScrubber.h"
#include "IllegalArgumentException.h"
#include "Memento.h"

#define VIDEOSTRINGID "video"

namespace model {
namespace player {

using ::model::video::Video;
using ::model::video::VideoMetadata;
using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;

VideoScrubber::VideoScrubber(video::Video::sptr video): video(video) {
	if (video->isDummy()) {
		throw new exception::IllegalArgumentException("Tried to use a dummy Video to create a VideoScrubber");
	}
	waitingForFrame = true;
	currentFrame = video->getFrame(0);
	waitingForFrame = false;
}

VideoScrubber::~VideoScrubber() {

}

VideoScrubber::VideoScrubber(video::Video::sptr video, unsigned int frameNumber) {
	if (video->isDummy()) {
		throw new exception::IllegalArgumentException("Tried to use a dummy Video to create a VideoScrubber");
	}
	waitingForFrame = true;
	currentFrame = video->getFrame(frameNumber);
	waitingForFrame = false;
}

VideoScrubber::VideoScrubber()
{
	isDummyFlag = true;
}

VideoMetadata VideoScrubber::getVideoMetadata() const {
	if (isDummy()) {
		throw new exception::IllegalStateException("Requested VideoMetadata from dummy VideoScrubber.");
	}

	return video->getMetadata();
}

Video::sptr VideoScrubber::getVideo() const {
	if (isDummy()) {
		throw new exception::IllegalStateException("Requested Video from dummy VideoScrubber.");
	}

	return video;
}

Frame::sptr VideoScrubber::getCurrentFrame() const{
	if (isDummy()) {
		throw new exception::IllegalStateException("Requested Frame from dummy VideoScrubber.");
	}

	return currentFrame;
}

bool VideoScrubber::isWaitingForFrame() const {
	if (isDummy()) {
		throw new exception::IllegalStateException("Asked dummy VideoScrubber whether it's waiting for a Frame.");
	}

	return waitingForFrame;
}

void VideoScrubber::jumpToFrameNr(unsigned int frameNumber) {
	if (isDummy()) {
		throw new exception::IllegalStateException("Requested a frame jump from dummy VideoScrubber.");
	}

	waitingForFrame = true;
	currentFrame = video->getFrame(frameNumber);
	waitingForFrame = false;
	changed();
}

Memento VideoScrubber::getMemento() const {
	if (isDummy()) {
		throw new exception::IllegalStateException("Requested a memento from a dummy VideoScrubber.");
	}

	Memento memento;
	memento.setSharedPointer(VIDEOSTRINGID, video);
	return memento;
}

void VideoScrubber::restore(Memento memento) {
	//TODO ykrjgh warum tut das nicht???
	//video = memento.getSharedPointer<Video>(VIDEOSTRINGID);

// 	waitingForFrame = true;
// 	currentFrame = video->getFrame(0);
// 	waitingForFrame = false;
// 
// 	isDummyFlag = false;
}

Saveable::sptr VideoScrubber::getDummy() {
	return VideoScrubber::sptr(new VideoScrubber());
}

unsigned int VideoScrubber::getFrameCount() const
{
	return video->getFrameCount();
}

inline bool operator==(VideoScrubber &lhs, VideoScrubber &rhs) { return lhs.video == rhs.video; }
inline bool operator!=(VideoScrubber &lhs, VideoScrubber &rhs) { return !operator==(lhs, rhs); }

}  // namespace player
}  // namespace model