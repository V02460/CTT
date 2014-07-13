#include "MacroblockOverlay.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;

MacroblockOverlay::MacroblockOverlay(Module::sptr predecessor) : ColoringOverlay(predecessor) {

}

MacroblockOverlay::~MacroblockOverlay() {

}

QString MacroblockOverlay::getName() const {

}

model::frame::Frame::sptr MacroblockOverlay::getFrame(unsigned int frameNumber) const {

}

}  // namespace overlay
}  // namespace filter
}  // namcespace model