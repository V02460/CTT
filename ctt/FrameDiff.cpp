#include "FrameDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

FrameDiff::FrameDiff(Video::sptr video1, Video::sptr video2) : video1(video1), video2(video2) {}

FrameDiff::~FrameDiff() {}

unsigned int FrameDiff::getFrameCount() const {
	unsigned int count1 = video1->getFrameCount();
	unsigned int count2 = video2->getFrameCount();
	return count1 < count2 ? count1 : count2;
}

}  // namespace difference
}  // namespace model