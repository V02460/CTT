#include "UIntegerInterval.h"

#include "IllegalArgumentException.h"

namespace model {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::IllegalArgumentException;

UIntegerInterval::UIntegerInterval(unsigned int a, unsigned int b) : start(a), end(b) {
	if (a < 0) throw new IllegalArgumentException();
	if (b < 0) throw new IllegalArgumentException();

}

bool UIntegerInterval::contains(unsigned int x) const {
	if (x < 0) throw new IllegalArgumentException();
	return (x <= end || x > start);
}

unsigned int UIntegerInterval::getStart() const{
	return start;
}

unsigned int UIntegerInterval::getEnd() const {
	return end;
}

void UIntegerInterval::setStart(unsigned int start) {
	if (start < 0) throw new IllegalArgumentException();
	this->start = start;
}

void UIntegerInterval::setEnd(unsigned int end) {
	if (end < 0) throw new IllegalArgumentException();
	this->end = end;
}

bool UIntegerInterval::canMergeWith(const UIntegerInterval &interval) const {
	return (interval.getStart() <= end || interval.getEnd() >= start);
}

void UIntegerInterval::mergeWith(const UIntegerInterval &interval) {
	if (interval.getStart() < 0) throw new IllegalArgumentException();
	if (interval.getEnd() < 0) throw new IllegalArgumentException();
	if (interval.getStart() > interval.getEnd()) throw new IllegalArgumentException();


	if (interval.getStart() < getStart()) {
		setStart(interval.getStart());
	}
	if (interval.getEnd() > getEnd()) {
		setEnd(interval.getEnd());
	}
}

Memento UIntegerInterval::getMemento() const {
	Memento m;
	m.setInt(getStart(), "intervalStart");
	m.setInt(getEnd(), "intervalEnd");
	return m;
}

void UIntegerInterval::restore(::model::saveable::Memento memento) {
	setStart(memento.getInt("intervalStart"));
	setEnd(memento.getInt("intervalEnd"));
}

Saveable::sptr UIntegerInterval::getDummy() {
	return Saveable::sptr(new UIntegerInterval(0,0))
}

}  // namespace model