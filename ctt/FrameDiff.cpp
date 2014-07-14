#include "FrameDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;

FrameDiff::FrameDiff(Video::sptr video1, Video::sptr video2) {
    throw new NotImplementedException();
}

FrameDiff::~FrameDiff() {
    throw new NotImplementedException();
}

unsigned int FrameDiff::getFrameCount() const {
    throw new NotImplementedException();
}

}  // namespace difference
}  // namespace model