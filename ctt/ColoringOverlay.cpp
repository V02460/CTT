#include "ColoringOverlay.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::model::filter::GreyscaleFilter;

ColoringOverlay::ColoringOverlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha)
        : greyscaleFilter(new GreyscaleFilter(predecessor))
        , Overlay(greyscaleFilter, overlay, overlayAlpha) {
}

ColoringOverlay::~ColoringOverlay() {
}

}  // namespace overlay
}  // namespace filter
}  // namespace model