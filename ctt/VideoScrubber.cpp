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
using ::exception::AccessToDummyException;

const QString VideoScrubber::videoStringId("video");
const QString VideoScrubber::lastFrameNumberStringId("framenr");

VideoScrubber::VideoScrubber(video::Video::sptr video) : Observable() ,video(video), lastFrameNumber(0) {
	if (video->isDummy()) {
		throw IllegalArgumentException("Tried to use a dummy Video to create a VideoScrubber");
	}
	waitingForFrame = true;
	currentFrame = video->getFrame(0);
	waitingForFrame = false;

	video->subscribe(this);
}

VideoScrubber::~VideoScrubber() {
	video->unsubscribe(this);
}

VideoScrubber::VideoScrubber(video::Video::sptr video, unsigned int frameNumber) : Observable() {
	if (video->isDummy()) {
		throw IllegalArgumentException("Tried to use a dummy Video to create a VideoScrubber");
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
		throw AccessToDummyException();
	}
	return video->getMetadata();
}

Video::sptr VideoScrubber::getVideo() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return video;
}

Frame::sptr VideoScrubber::getCurrentFrame() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (currentFrame.isNull())
	{
		return video->getFrame(lastFrameNumber);
	}

	return currentFrame;
}

bool VideoScrubber::isWaitingForFrame() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return waitingForFrame;
}

void VideoScrubber::jumpToFrameNr(unsigned int frameNumber) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (!isWaitingForFrame())
	{
		waitingForFrame = true;
		currentFrame = video->getFrame(frameNumber);
		waitingForFrame = false;
		lastFrameNumber = frameNumber;
		changed();
	}
}

Memento VideoScrubber::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
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
		throw IllegalArgumentException("Unable to restore, pointer received from Memento could'nt be cast to the right type.");
	}

	lastFrameNumber = memento.getUInt(lastFrameNumberStringId);
	isDummyFlag = false;
}

Saveable::sptr VideoScrubber::getDummy() {
	return VideoScrubber::sptr(new VideoScrubber());
}

Saveable::SaveableType VideoScrubber::getSaveableType() {
    return SaveableType::videoScrubber;
}

unsigned int VideoScrubber::getFrameCount() const
{
	return video->getFrameCount();
}

void VideoScrubber::update()
{
	jumpToFrameNr(lastFrameNumber);
}

inline bool operator==(VideoScrubber &lhs, VideoScrubber &rhs) { return lhs.video == rhs.video; }
inline bool operator!=(VideoScrubber &lhs, VideoScrubber &rhs) { return !operator==(lhs, rhs); }

}  // namespace player
}  // namespace model