#include "HSLPixelDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;

HSLPixelDiff::HSLPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
    throw new NotImplementedException();
}

HSLPixelDiff::~HSLPixelDiff() {
    throw new NotImplementedException();
}

Surface HSLPixelDiff::getPixelDiff(unsigned int frameNr) const {
    throw new NotImplementedException();
}

double HSLPixelDiff::getDiff(unsigned int frameNr) const{
    throw new NotImplementedException();
}

}  // namespace difference
}  // namespace model