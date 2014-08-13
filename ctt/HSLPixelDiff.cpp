#include "HSLPixelDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

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

Saveable::SaveableType HSLPixelDiff::getType() const {
	return Saveable::SaveableType::hSLPixelDiff;
}

}  // namespace difference
}  // namespace model