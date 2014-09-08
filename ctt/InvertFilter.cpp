#include "InvertFilter.h"

#include "GPUSurfaceShader.h"

#include "AccessToDummyException.h"
#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUSurfaceShader;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;

const QByteArray InvertFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_invert");

InvertFilter::InvertFilter(Module::sptr predecessor) : Filter(predecessor) {
}

InvertFilter::~InvertFilter() {}

model::frame::Frame::sptr InvertFilter::getFrame(unsigned int frameNumber) const {
    if (isDummy()) {
        throw AccessToDummyException();
    }

    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUSurfaceShader gpuHelper(":/Shader/Filter/Invert.fs", frame.staticCast<Surface>());

    Surface::sptr targetSurface = gpuHelper.run();

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Memento InvertFilter::getMemento() const {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    return Filter::getMemento();
}

void InvertFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> InvertFilter::getUsesList() const {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    return QList<const Module*>() << this;
}

Saveable::sptr InvertFilter::getDummy() {
    return InvertFilter::sptr(new InvertFilter());
}

InvertFilter::InvertFilter() {
    isDummyFlag = true;
}

}  // namespace filter
}  // namespace model