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
        : Overlay(GreyscaleFilter::sptr(new GreyscaleFilter(predecessor)), overlay, overlayAlpha) {
}

ColoringOverlay::~ColoringOverlay() {
}

}  // namespace overlay
}  // namespace filter
}  // namespace model