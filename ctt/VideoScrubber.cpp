#include "VideoScrubber.h"

namespace model {
namespace player {

using ::model::video::Video;
using ::model::video::VideoMetadata;
using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;

VideoScrubber::VideoScrubber(video::Video::sptr video) {

}

VideoScrubber::~VideoScrubber() {

}

VideoScrubber::VideoScrubber(video::Video::sptr video, unsigned int frameNumber) {

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