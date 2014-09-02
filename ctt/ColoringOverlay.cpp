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

ColoringOverlay::ColoringOverlay(Module::sptr greyscaleFilter,
                                 Module::sptr predecessor,
                                 Module::sptr overlay,
                                 float overlayAlpha)
        : Overlay(greyscaleFilter, overlay, overlayAlpha)
        , greyscaleFilter(greyscaleFilter) {
}

ColoringOverlay::ColoringOverlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha)
        : ColoringOverlay(GreyscaleFilter::sptr(new GreyscaleFilter(predecessor))
        , predecessor
        , overlay
        , overlayAlpha) {
}

ColoringOverlay::~ColoringOverlay() {
}

Memento ColoringOverlay::getMemento() const {
	return Overlay::getMemento();
}

void ColoringOverlay::restore(::model::saveable::Memento memento) {
	Overlay::restore(memento);
}

QList<const Module*> ColoringOverlay::getUsesList() const {
    QList<const Module*> list = Overlay::getUsesList();

    return list << greyscaleFilter.data();
}

Saveable::sptr ColoringOverlay::getDummy() {
	throw NotImplementedException();
}

ColoringOverlay::ColoringOverlay() : Overlay() {
    isDummyFlag = true;
}

}  // namespace overlay
}  // namespace filter
}  // namespace model