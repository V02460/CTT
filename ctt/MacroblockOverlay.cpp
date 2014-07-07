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

Frame MacroblockOverlay::getFrame(unsigned int frameNumber) const {

}

}  // namespace overlay
}  // namespace filter
}  // namcespace model