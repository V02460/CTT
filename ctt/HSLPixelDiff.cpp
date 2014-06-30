#include "HSLPixelDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

HSLPixelDiff::HSLPixelDiff(const video::Video &video1, const video::Video &video2) : PixelDiff(video1, video2) {
	
}

Surface HSLPixelDiff::getPixelDiff(unsigned int frameNr) const {

}

double HSLPixelDiff::getDiff(unsigned int frameNr) const{

}

}  // namespace difference
}  // namcespace model