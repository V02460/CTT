#include "UIntegerInterval.h"

#include "IllegalArgumentException.h"
#include "AccessToDummyException.h"

namespace model {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::IllegalArgumentException;
using ::exception::AccessToDummyException;

UIntegerInterval::UIntegerInterval(unsigned int start, unsigned int end) : start(start), end(end) {
	if (start > end) {
		throw new IllegalArgumentException("start > end");
	}
}

UIntegerInterval::UIntegerInterval() {
	isDummyFlag = true;
}

bool UIntegerInterval::contains(unsigned int x) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	return (start <= x && x <= end);
}

unsigned int UIntegerInterval::getStart() const{
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	return start;
}

unsigned int UIntegerInterval::getEnd() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	return end;
}

void UIntegerInterval::setStart(unsigned int newStart) {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	if (newStart > end) {
		throw new IllegalArgumentException("start > end");
	}
	start = newStart;
}

void UIntegerInterval::setEnd(unsigned int newEnd) {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	if (start > newEnd) {
		throw new IllegalArgumentException("start > end");
	}
	end = newEnd;
}

bool UIntegerInterval::canMergeWith(const UIntegerInterval &interval) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	return (!(interval.getEnd() < start || end < interval.getStart()));
}

void UIntegerInterval::mergeWith(const UIntegerInterval &interval) {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	if (!canMergeWith(interval)) {
		throw new IllegalArgumentException("Intervals can't merge.");
	}
	setStart(std::min(start, interval.getStart()));
	setEnd(std::max(end, interval.getEnd()));
}

Memento UIntegerInterval::getMemento() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	Memento memento;
    memento.setInt("intervalStart", start);
    memento.setInt("intervalEnd", end);
	return memento;
}

void UIntegerInterval::restore(::model::saveable::Memento memento) {
	setStart(memento.getInt("intervalStart"));
	setEnd(memento.getInt("intervalEnd"));
	if (start > end) {
		throw new IllegalArgumentException("start > end");
	}
	isDummyFlag = false;
}

Saveable::sptr UIntegerInterval::getDummy() {
	return Saveable::sptr(new UIntegerInterval());
}

Saveable::SaveableType UIntegerInterval::getSaveableType() {
    return SaveableType::uIntegerInterval;
}

}  // namespace model