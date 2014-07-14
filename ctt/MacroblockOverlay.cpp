#include "MacroblockOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

MacroblockOverlay::MacroblockOverlay(Module::sptr predecessor) : ColoringOverlay(predecessor) {
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

}  // namespace overlay
}  // namespace filter
}  // namespace model