#include "ColoringOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::filter::GreyscaleFilter;

ColoringOverlay::ColoringOverlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha)
        : greyscaleFilter(new GreyscaleFilter(predecessor))
        , Overlay(greyscaleFilter, overlay, overlayAlpha) {
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

Saveable::SaveableType ColoringOverlay::getSaveableType() {
    return SaveableType::coloringOverlay;
}

}  // namespace overlay
}  // namespace filter
}  // namespace model