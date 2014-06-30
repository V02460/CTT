#include "YUVPixelDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

YUVPixelDiff::YUVPixelDiff(const video::Video &video1, const video::Video &video2) : PixelDiff(video1, video2) {

}

YUVPixelDiff::~YUVPixelDiff() {

}

Surface	YUVPixelDiff::getPixelDiff(unsigned int frameNr) const {

}

double YUVPixelDiff::getDiff(unsigned int frameNr) const {

}

}  // namespace difference
}  // namcespace model