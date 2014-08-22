#include "VideoScrubber.h"

#include "IllegalArgumentException.h"
#include "IllegalStateException.h"
#include "NotImplementedException.h"


namespace model {
namespace player {

using ::model::video::Video;
using ::model::video::VideoMetadata;
using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
using ::exception::IllegalArgumentException;
using ::exception::IllegalStateException;

const QString VideoScrubber::videoStringId("video");
const QString VideoScrubber::lastFrameNumberStringId("framenr");

VideoScrubber::VideoScrubber(video::Video::sptr video): video(video), lastFrameNumber(0) {
	if (video->isDummy()) {
		throw new IllegalArgumentException("Tried to use a dummy Video to create a VideoScrubber");
	}
	waitingForFrame = true;
	currentFrame = video->getFrame(0);
	waitingForFrame = false;
}

VideoScrubber::~VideoScrubber() {

}

VideoScrubber::VideoScrubber(video::Video::sptr video, unsigned int frameNumber) {
	if (video->isDummy()) {
		throw new IllegalArgumentException("Tried to use a dummy Video to create a VideoScrubber");
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
		throw new IllegalStateException("Requested VideoMetadata from dummy VideoScrubber.");
	}

	return video->getMetadata();
}

Video::sptr VideoScrubber::getVideo() const {
	if (isDummy()) {
		throw new IllegalStateException("Requested Video from dummy VideoScrubber.");
	}

	return video;
}

Frame::sptr VideoScrubber::getCurrentFrame() const{
	if (isDummy()) {
		throw new IllegalStateException("Requested Frame from dummy VideoScrubber.");
	}

	if (currentFrame.isNull())
	{
		return video->getFrame(lastFrameNumber);
	}

	return currentFrame;
}

bool VideoScrubber::isWaitingForFrame() const {
	if (isDummy()) {
		throw new IllegalStateException("Asked dummy VideoScrubber whether it's waiting for a Frame.");
	}

	return waitingForFrame;
}

void VideoScrubber::jumpToFrameNr(unsigned int frameNumber) {
	if (isDummy()) {
		throw new IllegalStateException("Requested a frame jump from dummy VideoScrubber.");
	}

	if (!isWaitingForFrame())
	{
		waitingForFrame = true;
		currentFrame = video->getFrame(frameNumber);
		waitingForFrame = false;
		changed();
	}
}

Memento VideoScrubber::getMemento() const {
	if (isDummy()) {
		throw new exception::IllegalStateException("Requested a memento from a dummy VideoScrubber.");
	}

	Memento memento;
	memento.setSharedPointer(videoStringId, video);
	memento.setUInt(lastFrameNumberStringId, lastFrameNumber);
	return memento;
}

void VideoScrubber::restore(Memento memento) {
 	video = memento.getSharedPointer(videoStringId).dynamicCast<Video>();

	if (video.isNull())
	{
		throw new IllegalArgumentException("Unable to restore, pointer received from Memento could'nt be cast to the right type.");
	}

	lastFrameNumber = memento.getUInt(lastFrameNumberStringId);

	isDummyFlag = false;
}

Saveable::sptr VideoScrubber::getDummy() {
	return VideoScrubber::sptr(new VideoScrubber());
}

Saveable::SaveableType VideoScrubber::getType() const {
	return Saveable::SaveableType::videoScrubber;
}

unsigned int VideoScrubber::getFrameCount() const
{
	return video->getFrameCount();
}

inline bool operator==(VideoScrubber &lhs, VideoScrubber &rhs) { return lhs.video == rhs.video; }
inline bool operator!=(VideoScrubber &lhs, VideoScrubber &rhs) { return !operator==(lhs, rhs); }

}  // namespace player
}  // namespace model