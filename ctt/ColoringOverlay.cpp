#include "ColoringOverlay.h"

#include "NotImplementedException.h"

// TODO bei Implementierung bitte an saveable dinge denken!

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

ColoringOverlay::ColoringOverlay(Module::sptr predecessor) : Overlay(predecessor) {
    throw new NotImplementedException();
}

ColoringOverlay::~ColoringOverlay() {
    throw new NotImplementedException();
}

QString ColoringOverlay::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr ColoringOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Memento ColoringOverlay::getMemento() const {
	throw new NotImplementedException();
}

void ColoringOverlay::restore(::model::saveable::Memento memento) {
	throw new NotImplementedException();
}

QList<const Module*> ColoringOverlay::getUsesList() const {
	throw new NotImplementedException();
}

Saveable::sptr ColoringOverlay::getDummy() {
	throw new NotImplementedException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model