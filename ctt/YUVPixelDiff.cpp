#include "YUVPixelDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;

YUVPixelDiff::YUVPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {

}

YUVPixelDiff::~YUVPixelDiff() {

}

Surface YUVPixelDiff::getPixelDiff(unsigned int frameNr) const {

}

double YUVPixelDiff::getDiff(unsigned int frameNr) const {

}

Memento YUVPixelDiff::getMemento() const {

}

void YUVPixelDiff::restore(::model::saveable::Memento memento) {

}

Saveable::sptr YUVPixelDiff::getDummy() {

}

}  // namespace difference
}  // namespace model