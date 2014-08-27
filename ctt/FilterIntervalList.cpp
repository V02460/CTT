#include "FilterIntervalList.h"

#include "NotImplementedException.h"
#include "IllegalArgumentException.h"

namespace model {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;

FilterIntervalList::FilterIntervalList() {
		intervals.clear();
}


bool FilterIntervalList::isActive(unsigned int frameNumber) const {
		if (frameNumber < 0) throw new exception::IllegalArgumentException();
		for (int i = 0; i < intervals.length(); i++) {
			if (intervals.at(i).contains(frameNumber)) {
				return true;
}
		}
		return false;
	}


void FilterIntervalList::activate(UIntegerInterval interval) {
		intervals.append(interval);
}


void FilterIntervalList::deactivate(UIntegerInterval interval) {
		for (int i = 0; i < intervals.length(); i++) {
			for (int j = interval.getStart(); j = interval.getEnd(); j++){
				if (interval.contains(j)) {
					intervals.removeAt(i);
}
			}
		}
	}


QList<UIntegerInterval> FilterIntervalList::getIntervalList() const {
		return intervals;
}

Memento FilterIntervalList::getMemento() const {
		Memento m;
		for (int i = 0; i < intervals.length(); i++) {
			m.setInt("intervalStart" + i, intervals.at(i).getStart());
			m.setInt("intervalEnd" + i, intervals.at(i).getEnd());
		}
		m.setInt("length", intervals.length());
		return m;
}

void FilterIntervalList::restore(Memento memento) {
		int length = memento.getInt("length");
		for (int i = 0; i < length; i++) {
			unsigned int start = memento.getInt("intervalStart" + i);
			unsigned int end = memento.getInt("intervalEnd" + i);

			activate(UIntegerInterval(start, end));
		}
}

Saveable::sptr FilterIntervalList::getDummy() {
		return Saveable::sptr(new FilterIntervalList());
}

Saveable::SaveableType FilterIntervalList::getSaveableType() {
    return SaveableType::filterIntervalList;
}

}  // namespace model