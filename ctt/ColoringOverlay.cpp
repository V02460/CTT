#include "ColoringOverlay.h"

#include "NotImplementedException.h"

// TODO bei Implementierung bitte an saveable dinge denken!

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::filter::GreyscaleFilter;
using ::model::saveable::Memento;

ColoringOverlay::ColoringOverlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha)
        : Overlay(GreyscaleFilter::sptr(new GreyscaleFilter(predecessor)), overlay, overlayAlpha) {
}

ColoringOverlay::~ColoringOverlay() {
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