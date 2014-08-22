#include "MacroblockOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

MacroblockOverlay::MacroblockOverlay(Module::sptr predecessor) : ColoringOverlay(predecessor, XXX, 0.5) {
    throw new NotImplementedException();
}

MacroblockOverlay::~MacroblockOverlay() {
    throw new NotImplementedException();
}

QString MacroblockOverlay::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr MacroblockOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType MacroblockOverlay::getType() const {
	return Saveable::SaveableType::macroblockOverlay;
}

}  // namespace overlay
}  // namespace filter
}  // namespace model