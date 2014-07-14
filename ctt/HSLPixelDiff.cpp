#include "HSLPixelDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;

HSLPixelDiff::HSLPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
    
}

HSLPixelDiff::~HSLPixelDiff() {

}

Surface HSLPixelDiff::getPixelDiff(unsigned int frameNr) const {

}

double HSLPixelDiff::getDiff(unsigned int frameNr) const{

}

Memento HSLPixelDiff::getMemento() const {

}

void HSLPixelDiff::restore(::model::saveable::Memento memento) {

}

Saveable::sptr HSLPixelDiff::getDummy() {

}

}  // namespace difference
}  // namespace model