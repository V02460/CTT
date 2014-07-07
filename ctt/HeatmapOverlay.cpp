#include "HeatmapOverlay.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::difference::PixelDiff;
using ::model::frame::Frame;

HeatmapOverlay::HeatmapOverlay(Module::sptr predecessor, PixelDiff::sptr difference) : ColoringOverlay(predecessor) {

}

HeatmapOverlay::~HeatmapOverlay() {

}

QString HeatmapOverlay::getName() const {

}

Frame HeatmapOverlay::getFrame(unsigned int frameNumber) const {

}

}  // namespace overlay
}  // namespace filter
}  // namespace model