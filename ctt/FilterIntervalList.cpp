#include "FilterIntervalList.h"
#include "UIntegerInterval.h"
#include "Saveable.h"
#include "Memento.h"

namespace model {

FilterIntervalList::FilterIntervalList() {
}


bool FilterIntervalList::isActive(unsigned int frameNumber) {
}


void FilterIntervalList::activate(UIntegerInterval interval) {
}


void FilterIntervalList::deactivate(UIntegerInterval interval) {
}


QList<UIntegerInterval> FilterIntervalList::getIntervalList() {
}

}  // namespace model