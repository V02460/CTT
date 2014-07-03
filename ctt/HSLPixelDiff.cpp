#include "HSLPixelDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;

HSLPixelDiff::HSLPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
    
}

Surface HSLPixelDiff::getPixelDiff(unsigned int frameNr) const {

}

double HSLPixelDiff::getDiff(unsigned int frameNr) const{

}

}  // namespace difference
}  // namcespace model