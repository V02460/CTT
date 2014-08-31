#include "HeatmapOverlay.h"

#include "NotImplementedException.h"

// TODO bei Implementierung bitte an saveable dinge denken!

namespace model {
namespace filter {
namespace overlay {

using ::model::difference::PixelDiff;
using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

const QByteArray HeatmapOverlay::kFilterID = QT_TR_NOOP("overlay_heatmap");

HeatmapOverlay::HeatmapOverlay(Module::sptr predecessor, PixelDiff::sptr difference) : ColoringOverlay(predecessor) {
    throw new NotImplementedException();
}

HeatmapOverlay::~HeatmapOverlay() {
    throw new NotImplementedException();
}

model::frame::Frame::sptr HeatmapOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Memento HeatmapOverlay::getMemento() const {
	throw new NotImplementedException();
}

void HeatmapOverlay::restore(::model::saveable::Memento memento) {
	throw new NotImplementedException();
}

QList<const Module*> HeatmapOverlay::getUsesList() const {
	throw new NotImplementedException();
}

Saveable::sptr HeatmapOverlay::getDummy() {
	throw new NotImplementedException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model