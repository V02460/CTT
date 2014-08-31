#include "CoffeeFilter.h"
#include "Frame.h"
#include "Memento.h"

#include "NotImplementedException.h"
#include "AccessToDummyException.h"

// TODO implement

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::AccessToDummyException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

const QByteArray CoffeeFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_coffee");

CoffeeFilter::CoffeeFilter(Module::sptr predecessor) : Filter(predecessor) {}

CoffeeFilter::CoffeeFilter() {
	isDummyFlag = true;
}

CoffeeFilter::~CoffeeFilter() {}

model::frame::Frame::sptr CoffeeFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return getPredecessor()->getFrame(frameNumber);
}

Memento CoffeeFilter::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    return Filter::getMemento();
}

void CoffeeFilter::restore(Memento memento) {
	Filter::restore(memento);
	isDummyFlag = false;
}

QList<const Module*> CoffeeFilter::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return QList<const Module*>() << this;
}

Saveable::sptr CoffeeFilter::getDummy() {
	return CoffeeFilter::sptr(new CoffeeFilter());
}

}  // namespace filter
}  // namespace model