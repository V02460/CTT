#include "FilterIntervalList.h"

#include "NotImplementedException.h"

namespace model {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;

FilterIntervalList::FilterIntervalList() {
    //throw new NotImplementedException();
}


bool FilterIntervalList::isActive(unsigned int frameNumber) const {
    throw new NotImplementedException();
}


void FilterIntervalList::activate(UIntegerInterval interval) {
    throw new NotImplementedException();
}


void FilterIntervalList::deactivate(UIntegerInterval interval) {
    throw new NotImplementedException();
}


QList<UIntegerInterval> FilterIntervalList::getIntervalList() const {
    throw new NotImplementedException();

}

Memento FilterIntervalList::getMemento() const {
    throw new NotImplementedException();

}

void FilterIntervalList::restore(Memento memento) {
    throw new NotImplementedException();

}

Saveable::sptr FilterIntervalList::getDummy() {
    throw new NotImplementedException();
}

Saveable::SaveableType FilterIntervalList::getSaveableType() {
    return SaveableType::filterIntervalList;
}

}  // namespace model