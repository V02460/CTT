#include "GreyscaleFilter.h"

#include "GPUSurfaceShader.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUSurfaceShader;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;

const QByteArray GreyscaleFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_greyscale");

GreyscaleFilter::GreyscaleFilter(Module::sptr predecessor) : Filter(predecessor) {}

GreyscaleFilter::GreyscaleFilter() {
	isDummyFlag = true;
}

GreyscaleFilter::~GreyscaleFilter() {}

Frame::sptr GreyscaleFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUSurfaceShader gpuHelper(":/Shader/Filter/Greyscale.fs", frame.staticCast<Surface>());

    Surface::sptr targetSurface = gpuHelper.run();

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Memento GreyscaleFilter::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    return Filter::getMemento();
}

void GreyscaleFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> GreyscaleFilter::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    return QList<const Module*>() << this;
}

Saveable::sptr GreyscaleFilter::getDummy() {
	return GreyscaleFilter::sptr(new GreyscaleFilter());
}

}  // namespace filter
}  // namespace model