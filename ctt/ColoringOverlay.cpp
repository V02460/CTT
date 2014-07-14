#include "ColoringOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

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

}  // namespace overlay
}  // namespace filter
}  // namespace model