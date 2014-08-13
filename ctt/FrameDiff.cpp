#include "FrameDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

FrameDiff::FrameDiff(Video::sptr video1, Video::sptr video2) : video1(video1), video2(video2) {}

FrameDiff::FrameDiff() {}

FrameDiff::~FrameDiff() {}

unsigned int FrameDiff::getFrameCount() const {
	return std::min(video1->getFrameCount(), video2->getFrameCount());
}

}  // namespace difference
}  // namespace model