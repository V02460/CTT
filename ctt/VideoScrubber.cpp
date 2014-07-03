#include "VideoScrubber.h"

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

bool VideoScrubber::isWaitingForFrame() const {

}

void VideoScrubber::jumpToFrameNr(unsigned int frameNumber) {

}

}  // namespace player
}  // namespace model