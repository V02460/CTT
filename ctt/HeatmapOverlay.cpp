#include "HeatmapOverlay.h"

#include "GPUSurfaceShader.h"
#include "FrameMetadata.h"
#include "NotImplementedException.h"

// TODO bei Implementierung bitte an saveable dinge denken!

namespace model {
namespace filter {
namespace overlay {

using ::model::difference::PixelDiff;
using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::helper::GPUSurfaceShader;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::NotImplementedException;

const QByteArray HeatmapOverlay::kFilterID = QT_TR_NOOP("overlay_heatmap");

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

QList<const Module*> HeatmapOverlay::getUsesList() const {
    QList<const ::model::Module*> list;

    return list << this
                << heatmap.data();
}

Memento HeatmapOverlay::getMemento() const {
    throw NotImplementedException();
}

void HeatmapOverlay::restore(Memento memento) {
    throw NotImplementedException();
}

Frame::sptr HeatmapOverlay::Heatmap::getFrame(unsigned int frameNumber) const {
    Surface::sptr pixelDiff = difference->getPixelDiff(frameNumber);

    GPUSurfaceShader gpuHelper(":/Shader/Overlay/heatmap.fs", pixelDiff->getContext());
    gpuHelper.setSourceTexture(pixelDiff);
    Surface::sptr heatmapSurface = gpuHelper.run();

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
    throw NotImplementedException();
}

QList<const Module*> HeatmapOverlay::Heatmap::getUsesList() const {
    QList<const ::model::Module*> list;

    return list << this;
}

Saveable::sptr HeatmapOverlay::getDummy() {
    throw NotImplementedException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model