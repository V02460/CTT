#include "CoffeeFilter.h"
#include "Frame.h"
#include "Memento.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

CoffeeFilter::CoffeeFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

CoffeeFilter::~CoffeeFilter() {
    throw new NotImplementedException();
}

QString CoffeeFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr CoffeeFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Memento CoffeeFilter::getMemento() const {
    return Filter::getMemento();
}

void CoffeeFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> CoffeeFilter::getUsesList() const {
    return QList<const Module*>() << this;
}

Saveable::SaveableType CoffeeFilter::getType() const {
	return Saveable::SaveableType::coffeeFilter;
}

}  // namespace filter
}  // namespace model