#include "GreyscaleFilter.h"

#include "GPUSurfaceShader.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUSurfaceShader;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

GreyscaleFilter::GreyscaleFilter(Module::sptr predecessor) : Filter(predecessor) {
}

GreyscaleFilter::~GreyscaleFilter() {
}

Frame::sptr GreyscaleFilter::getFrame(unsigned int frameNumber) const {
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUSurfaceShader gpuHelper(":/Shader/Filter/Greyscale.fs", frame.staticCast<Surface>());

    Surface::sptr targetSurface = gpuHelper.run();

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Saveable::SaveableType GreyscaleFilter::getType() const {
	return Saveable::SaveableType::greyscaleFilter;
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

bool GreyscaleFilter::uses(const Module &module) const {
    return this == &module;
}

}  // namespace filter
}  // namespace model