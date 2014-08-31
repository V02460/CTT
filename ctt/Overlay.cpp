#include "Overlay.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::model::saveable::Saveable;

Overlay::Overlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha)
        : Filter(predecessor)
        , mixFilter(predecessor, overlay) {
    mixFilter.setParam(FilterParam(MixFilter::kParamMixRatioStr, overlayAlpha));
}

Overlay::~Overlay() {
}

Saveable::SaveableType Overlay::getSaveableType() {
    return SaveableType::overlay;
}

Frame::sptr Overlay::getFrame(unsigned int frameNumber) const {
    return mixFilter.getFrame(frameNumber);
}

}  // namespace overlay
}  // namespace filter
}  // namespace model