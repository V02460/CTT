#include "PixelDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

PixelDiff::PixelDiff(const video::Video &video1, const video::Video &video2) : FrameDiff(video1, video2){

}

PixelDiff::~PixelDiff() {

}

}  // namespace difference
}  // namcespace model