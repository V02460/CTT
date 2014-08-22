#include "PixelDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

PixelDiff::PixelDiff(Video::sptr video1, Video::sptr video2) : FrameDiff(video1, video2){

}

PixelDiff::~PixelDiff() {

}

Memento PixelDiff::getMemento() const {
    return FrameDiff::getMemento();
}

void PixelDiff::restore(::model::saveable::Memento memento) {
    FrameDiff::restore(memento);
}

PixelDiff::PixelDiff() : FrameDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model