#include "VideoScrubber.h"
#include "Frame.h"
#include "Video.h"
#include "VideoMetadata.h"
#include "Memento.h"

namespace model {
namespace player {

Frame VideoScrubber::getCurrentFrame() {

}

void VideoScrubber::jumpToFrameNr(unsigned int frameNumber); {

}

VideoScrubber::VideoScrubber(Video video) {

}

VideoScrubber::VideoScrubber(Video video, unsigned int frameNumber) {

}

VideoMetadata VideoScrubber::getVideoMetadata() {

}

Video VideoScrubber::getVideo() {

}

Memento VideoScrubber::getMemento() {

}

void VideoScrubber::restore(Memento memento) {

}

Saveable* VideoScrubber::getDummy() {

}

}  // namespace player
}  // namespace model