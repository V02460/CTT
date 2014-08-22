#include "YUVPixelDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

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

Memento YUVPixelDiff::getMemento() const {
    throw new NotImplementedException();
}

void YUVPixelDiff::restore(::model::saveable::Memento memento) {
    throw new NotImplementedException();
}

Saveable::sptr YUVPixelDiff::getDummy() {
    throw new NotImplementedException();
}

Saveable::SaveableType YUVPixelDiff::getType() const {
	return Saveable::SaveableType::yUVPixelDiff;
}

}  // namespace difference
}  // namespace model