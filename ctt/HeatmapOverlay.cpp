#include "HeatmapOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::difference::PixelDiff;
using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

HeatmapOverlay::HeatmapOverlay(Module::sptr predecessor, PixelDiff::sptr difference) : ColoringOverlay(predecessor) {
    throw new NotImplementedException();
}

HeatmapOverlay::~HeatmapOverlay() {
    throw new NotImplementedException();
}

QString HeatmapOverlay::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr HeatmapOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType HeatmapOverlay::getSaveableType() {
    return SaveableType::heatmapOverlay;
}

}  // namespace overlay
}  // namespace filter
}  // namespace model