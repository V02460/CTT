#include "FilterIntervalList.h"

namespace model {

using ::model::project::Memento;
using ::model::project::Saveable;

FilterIntervalList::FilterIntervalList() {
}


bool FilterIntervalList::isActive(unsigned int frameNumber) const {
}


void FilterIntervalList::activate(UIntegerInterval interval) {
}


void FilterIntervalList::deactivate(UIntegerInterval interval) {
}


QList<UIntegerInterval> FilterIntervalList::getIntervalList() const {

}

Memento FilterIntervalList::getMemento() const {

}

void FilterIntervalList::restore(Memento memento) {

}

Saveable::sptr FilterIntervalList::getDummy() {

}

}  // namespace model