#include "HeatmapOverlay.h"

#include "GPUSurfaceShader.h"
#include "FrameMetadata.h"
#include "GlobalContext.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::difference::PixelDiff;
using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::helper::GPUSurfaceShader;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::model::GlobalContext;
using ::exception::NotImplementedException;

const QByteArray HeatmapOverlay::kFilterID = QT_TRANSLATE_NOOP("Filter", "overlay_heatmap");

HeatmapOverlay::HeatmapOverlay(Module::sptr predecessor, PixelDiff::sptr difference, Heatmap::sptr heatmap)
        : ColoringOverlay(predecessor, heatmap, 1.0)
        , heatmap(heatmap) {
}

HeatmapOverlay::HeatmapOverlay(Module::sptr predecessor, PixelDiff::sptr difference)
    : HeatmapOverlay(predecessor, difference, Heatmap::sptr(new Heatmap(difference))) {
}

HeatmapOverlay::~HeatmapOverlay() {
}

HeatmapOverlay::Heatmap::Heatmap(PixelDiff::sptr difference)
        : difference(difference)
        , lookupTexture(Frame::sptr::create(GlobalContext::get(), QImage(":/Shader/Overlay/heatmapColors.png"))) {
}

HeatmapOverlay::Heatmap::~Heatmap() {
}

QList<const Module*> HeatmapOverlay::getUsesList() const {
    QList<const ::model::Module*> list;

    return list << this
                << heatmap.data();
}

Memento HeatmapOverlay::getMemento() const {
    Memento memento = ColoringOverlay::getMemento();

    memento.setSharedPointer(kHeatmapAttrStr, heatmap);

    return memento;
}

void HeatmapOverlay::restore(Memento memento) {
    ColoringOverlay::restore(memento);

    heatmap = memento.getSharedPointer(kHeatmapAttrStr).dynamicCast<Heatmap>();
}

Frame::sptr HeatmapOverlay::Heatmap::getFrame(unsigned int frameNumber) const {
    Surface::sptr pixelDiff = difference->getPixelDiff(frameNumber);

    GPUSurfaceShader gpuHelper(":/Shader/Overlay/Heatmap.fs", pixelDiff->getContext());
    gpuHelper.setSourceTexture(pixelDiff);
    gpuHelper.setValue("heatmapLookup", lookupTexture);
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

    lookupTexture = Frame::sptr::create(GlobalContext::get(), QImage(":/Shader/Overlay/heatmapColors.png"));
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

HeatmapOverlay::Heatmap::Heatmap() {
    isDummyFlag = true;
}

Saveable::sptr HeatmapOverlay::Heatmap::getDummy() {
    return HeatmapOverlay::Heatmap::sptr(new Heatmap());
}

HeatmapOverlay::HeatmapOverlay() {
    isDummyFlag = true;
}

Saveable::sptr HeatmapOverlay::getDummy() {
    return HeatmapOverlay::sptr(new HeatmapOverlay());
}

const QString HeatmapOverlay::kHeatmapAttrStr = "heatmap";

}  // namespace overlay
}  // namespace filter
}  // namespace model