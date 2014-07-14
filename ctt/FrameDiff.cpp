#include "FrameDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;

unsigned int FrameDiff::getFrameCount() const {
    return qMin(video1->getFrameCount(), video2->getFrameCount());
}

FrameDiff::FrameDiff(Video::sptr video1, Video::sptr video2) : video1(video1), video2(video2) {

}

FrameDiff::~FrameDiff() {

}

}  // namespace difference
}  // namespace model