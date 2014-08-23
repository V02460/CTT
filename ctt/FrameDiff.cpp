#include "FrameDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Saveable;

FrameDiff::FrameDiff(Video::sptr video1, Video::sptr video2) : video1(video1), video2(video2) {}

FrameDiff::~FrameDiff() {}

unsigned int FrameDiff::getFrameCount() const {
    return qMin(video1->getFrameCount(), video2->getFrameCount());
}

FrameDiff::FrameDiff() {
}

}  // namespace difference
}  // namespace model