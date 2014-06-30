#include "VideoScrubber.h"
#include "Frame.h"
#include "Video.h"
#include "VideoMetadata.h"
#include "Memento.h"

namespace model {
namespace player {

VideoScrubber::VideoScrubber(video::Video::sptr video) {

}

VideoScrubber::VideoScrubber(video::Video::sptr video, unsigned int frameNumber) {

}

video::VideoMetadata VideoScrubber::getVideoMetadata() const {

}

video::Video::wptr VideoScrubber::getVideo() const {

}

frame::Frame::wptr VideoScrubber::getCurrentFrame() const{

}

void VideoScrubber::jumpToFrameNr(unsigned int frameNumber); {

}

project::Memento VideoScrubber::getMemento() {

}

void VideoScrubber::restore(project::Memento memento) {

}

Saveable* VideoScrubber::getDummy() {

}

}  // namespace player
}  // namespace model