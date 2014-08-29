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

const QByteArray CoffeeFilter::kFilterID = QT_TR_NOOP("filter_coffee");

CoffeeFilter::CoffeeFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

CoffeeFilter::~CoffeeFilter() {
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
    throw new NotImplementedException();
}

bool CoffeeFilter::uses(const Module &module) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model