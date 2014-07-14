#include "YUVPixelDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;

YUVPixelDiff::YUVPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
    throw new NotImplementedException();
}

YUVPixelDiff::~YUVPixelDiff() {
    throw new NotImplementedException();
}

Surface YUVPixelDiff::getPixelDiff(unsigned int frameNr) const {
    throw new NotImplementedException();
}

double YUVPixelDiff::getDiff(unsigned int frameNr) const {
    throw new NotImplementedException();
}

}  // namespace difference
}  // namespace model