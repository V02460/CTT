#include "YUVPixelDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;

YUVPixelDiff::YUVPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {

}

YUVPixelDiff::~YUVPixelDiff() {

}

Surface YUVPixelDiff::getPixelDiff(unsigned int frameNr) const {

}

double YUVPixelDiff::getDiff(unsigned int frameNr) const {

}

}  // namespace difference
}  // namcespace model