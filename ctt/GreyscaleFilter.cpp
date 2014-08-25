#include "GreyscaleFilter.h"

#include "GPUHelper.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUHelper;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

GreyscaleFilter::GreyscaleFilter(Module::sptr predecessor) : Filter(predecessor) {
}

GreyscaleFilter::~GreyscaleFilter() {
}

Frame::sptr GreyscaleFilter::getFrame(unsigned int frameNumber) const {
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUHelper gpuHelper(":/Shader/Filter/Greyscale.fs", frame->getContext());

    Surface::sptr targetSurface = gpuHelper.run(*frame.data());

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Memento GreyscaleFilter::getMemento() const {
    return Filter::getMemento();
}

void GreyscaleFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> GreyscaleFilter::getUsesList() const {
    return QList<const Module*>() << this;
}

Saveable::SaveableType GreyscaleFilter::getSaveableType() {
    return SaveableType::greyscaleFilter;
}

bool GreyscaleFilter::uses(const Module &module) const {
    return this == &module;
}

}  // namespace filter
}  // namespace model