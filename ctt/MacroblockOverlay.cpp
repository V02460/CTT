#include "MacroblockOverlay.h"

#include "NotImplementedException.h"

// TODO bitte bei implementierung saveable dinge beachten

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

const QByteArray MacroblockOverlay::kFilterID = QT_TR_NOOP("overlay_macroblock");

MacroblockOverlay::MacroblockOverlay(Module::sptr predecessor) : ColoringOverlay(predecessor) {
    throw new NotImplementedException();
}

MacroblockOverlay::~MacroblockOverlay() {
    throw new NotImplementedException();
}

model::frame::Frame::sptr MacroblockOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType MacroblockOverlay::getSaveableType() {
    return SaveableType::macroblockOverlay;
}

void MacroblockOverlay::restore(::model::saveable::Memento memento) {
	throw new NotImplementedException();
}

QList<const Module*> MacroblockOverlay::getUsesList() const {
	throw new NotImplementedException();
}

Saveable::sptr MacroblockOverlay::getDummy() {
	throw new IllegalArgumentException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model