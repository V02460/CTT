#include "YUVPixelDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

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

Saveable::SaveableType YUVPixelDiff::getSaveableType() {
    return SaveableType::yUVPixelDiff;
}

}  // namespace difference
}  // namespace model