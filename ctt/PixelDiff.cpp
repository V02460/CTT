#include "PixelDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Saveable;

PixelDiff::PixelDiff(Video::sptr video1, Video::sptr video2) : FrameDiff(video1, video2){

}

PixelDiff::~PixelDiff() {

}

}  // namespace difference
}  // namcespace model