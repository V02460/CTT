#include "FilterIntervalList.h"

#include "NotImplementedException.h"
#include "IllegalArgumentException.h"
#include "AccessToDummyException.h"

namespace model {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;

FilterIntervalList::FilterIntervalList() : intervals() {}

bool FilterIntervalList::isActive(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	for each (UIntegerInterval::sptr interval in intervals) {
		if (interval->contains(frameNumber)) {
			return true;
		}
	}
	return false;
}

Saveable::SaveableType FilterIntervalList::saveableType() {
	return getSaveableType();
}

void FilterIntervalList::activate(UIntegerInterval::sptr newInterval) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	for each (UIntegerInterval::sptr interval in intervals) {
		if (newInterval->canMergeWith(*interval)) {
			newInterval->mergeWith(*interval);
			// TODO works?
			intervals.removeOne(interval);
		}
	}
	intervals.append(newInterval);
}


void FilterIntervalList::deactivate(UIntegerInterval::sptr toDelete) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	// TODO is that what should happen?
	// TODO works?
	if (!intervals.removeOne(toDelete)) {
		throw IllegalArgumentException("[" + QString::number(toDelete->getStart()) + ", " + toDelete->getEnd() +
			                               "] is not in the list.");
	}
}

QList<UIntegerInterval::sptr> FilterIntervalList::getIntervalList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return intervals;
}

Memento FilterIntervalList::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	Memento memento;
	memento.setInt("length", intervals.length());
	for (int i = 0; i < intervals.length(); i++) {
		memento.setSharedPointer("interval" + i, intervals[i]);
	}
	return memento;
}

void FilterIntervalList::restore(Memento memento) {
	int length = memento.getInt("length");
	for (int i = 0; i < length; i++) {
		intervals.append(memento.getSharedPointer("interval" + i).dynamicCast<UIntegerInterval>());
	}
}

Saveable::sptr FilterIntervalList::getDummy() {
	FilterIntervalList::sptr dummy(new FilterIntervalList());
	dummy->isDummyFlag = true;
	return dummy;
}

Saveable::SaveableType FilterIntervalList::getSaveableType() {
    return SaveableType::filterIntervalList;
}

}  // namespace model