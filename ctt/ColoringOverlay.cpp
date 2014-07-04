#include "ColoringOverlay.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;

ColoringOverlay::ColoringOverlay(Module::sptr predecessor) : Overlay(predecessor) {

}

ColoringOverlay::~ColoringOverlay() {

}

QString ColoringOverlay::getName() const {

}

Frame ColoringOverlay::getFrame(unsigned int frameNumber) const {

}

}  // namespace overlay
}  // namespace filter
}  // namcespace model