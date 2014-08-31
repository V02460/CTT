#include "PixelDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Saveable;

PixelDiff::PixelDiff(Video::sptr video1, Video::sptr video2) : FrameDiff(video1, video2) {}

PixelDiff::~PixelDiff() {}

Saveable::SaveableType PixelDiff::getSaveableType() {
    return SaveableType::pixelDiff;
}

}  // namespace difference
}  // namcespace model