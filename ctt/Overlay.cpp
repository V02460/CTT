#include "Overlay.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

const QString kMixFilterAttrStr = "mixFilter";

Overlay::Overlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha)
        : Filter(predecessor)
        , mixFilter(new MixFilter(predecessor, overlay)) {
    mixFilter->setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, overlayAlpha)));
}

Overlay::~Overlay() {
}

Saveable::SaveableType Overlay::getSaveableType() {
    return SaveableType::overlay;
}

Frame::sptr Overlay::getFrame(unsigned int frameNumber) const {
    return mixFilter->getFrame(frameNumber);
}

Memento Overlay::getMemento() const {
    Memento memento = Filter::getMemento();

    memento.setSharedPointer(kMixFilterAttrStr, mixFilter);

    return memento;
}

void Overlay::restore(Memento memento) {
    Filter::restore(memento);

    mixFilter = memento.getSharedPointer(kMixFilterAttrStr).dynamicCast<MixFilter>();
}

QList<const Module*> Overlay::getUsesList() const {
   return Filter::getUsesList() << mixFilter.data(); 
}

Overlay::Overlay() {
    isDummyFlag = true;
}

}  // namespace overlay
}  // namespace filter
}  // namespace model