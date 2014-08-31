#include "HeatmapOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::difference::PixelDiff;
using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

const QByteArray HeatmapOverlay::kFilterID = QT_TR_NOOP("overlay_heatmap");

HeatmapOverlay::HeatmapOverlay(Module::sptr predecessor, PixelDiff::sptr difference) : ColoringOverlay(predecessor) {
    throw new NotImplementedException();
}

HeatmapOverlay::~HeatmapOverlay() {
    throw new NotImplementedException();
}

model::frame::Frame::sptr HeatmapOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

QList<const ::model::Module*> HeatmapOverlay::getUsesList() const {
    throw new NotImplementedException();
}

bool HeatmapOverlay::uses(const ::model::Module &module) const {
    throw new NotImplementedException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model