#include "HSLPixelDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;

HSLPixelDiff::HSLPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
    throw new NotImplementedException();
}

HSLPixelDiff::~HSLPixelDiff() {
    throw new NotImplementedException();
}

Surface::sptr HSLPixelDiff::getPixelDiff(unsigned int frameNr) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    throw new NotImplementedException();
}

double HSLPixelDiff::getDiff(unsigned int frameNr) const{
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    throw new NotImplementedException();
}

Saveable::SaveableType HSLPixelDiff::getSaveableType() {
    return SaveableType::hSLPixelDiff;
}

Memento HSLPixelDiff::getMemento() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    throw new NotImplementedException();
}

void HSLPixelDiff::restore(::model::saveable::Memento memento) {
    throw new NotImplementedException();
}

Saveable::sptr HSLPixelDiff::getDummy() {
    throw new NotImplementedException();
}

}  // namespace difference
}  // namespace model