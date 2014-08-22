#include "HeatmapOverlay.h"

#include "GPUHelper.h"
#include "FrameMetadata.h"
#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::difference::PixelDiff;
using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::helper::GPUHelper;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::NotImplementedException;

HeatmapOverlay::HeatmapOverlay(Module::sptr predecessor, PixelDiff::sptr difference)
        : heatmap(new Heatmap(difference))
        , ColoringOverlay(predecessor, heatmap, 0.5) {
}

HeatmapOverlay::~HeatmapOverlay() {
}

HeatmapOverlay::Heatmap::Heatmap(PixelDiff::sptr difference) : difference(difference) {
}

HeatmapOverlay::Heatmap::~Heatmap() {
}

Frame::sptr HeatmapOverlay::Heatmap::getFrame(unsigned int frameNumber) const {
    Surface::sptr pixelDiff = difference->getPixelDiff(frameNumber);

    GPUHelper gpuHelper(":/Shader/Overlay/heatmap.fs", pixelDiff->getContext());
    Surface::sptr heatmapSurface = gpuHelper.run(*pixelDiff.data());

    return Frame::sptr(new Frame(heatmapSurface, FrameMetadata(pixelDiff->getSize())));
}

Memento HeatmapOverlay::Heatmap::getMemento() const {
    Memento memento;
    memento.setSharedPointer("difference", difference);
    return memento;
}

void HeatmapOverlay::Heatmap::restore(Memento memento) {
    difference = memento.getSharedPointer("difference").dynamicCast<PixelDiff>();
}

QSize HeatmapOverlay::Heatmap::getResolution() const {
    return difference->getPixelDiff(0)->getSize();
}

unsigned int HeatmapOverlay::Heatmap::getFrameCount() const {
    throw new NotImplementedException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model