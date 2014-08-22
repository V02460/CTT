#include "Overlay.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;

Overlay::Overlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha)
        : Filter(predecessor)
        , mixFilter(predecessor, overlay) {
    mixFilter.setParam(FilterParam("mixFactor", overlayAlpha));
}

Overlay::~Overlay() {
}

Frame::sptr Overlay::getFrame(unsigned int frameNumber) const {
    return mixFilter.getFrame(frameNumber);
}

}  // namespace overlay
}  // namespace filter
}  // namespace model