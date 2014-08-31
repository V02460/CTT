#include "GreyscaleFilter.h"

#include "GPUHelper.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUHelper;
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
		throw new AccessToDummyException();
	}
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUHelper gpuHelper(":/Shader/Filter/Greyscale.fs", frame->getContext());

    Surface::sptr targetSurface = gpuHelper.run(*frame.data());

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Memento GreyscaleFilter::getMemento() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    return Filter::getMemento();
}

void GreyscaleFilter::restore(Memento memento) {
    Filter::restore(memento);
	isDummyFlag = false;
}

QList<const Module*> GreyscaleFilter::getUsesList() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    return QList<const Module*>() << this;
}

Saveable::sptr GreyscaleFilter::getDummy() {
	return GreyscaleFilter::sptr(new GreyscaleFilter());
}

}  // namespace filter
}  // namespace model