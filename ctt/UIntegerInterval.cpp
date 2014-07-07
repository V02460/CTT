#include "UIntegerInterval.h"

namespace model {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;

UIntegerInterval::UIntegerInterval(unsigned int a, unsigned int b) {

}

bool UIntegerInterval::contains(unsigned int x) const {

}

unsigned int UIntegerInterval::getStart() const{

}

unsigned int UIntegerInterval::getEnd() const {

}

void UIntegerInterval::setStart(unsigned int start) {

}

void UIntegerInterval::setEnd(unsigned int end) {

}

bool UIntegerInterval::canMergeWith(UIntegerInterval interval) const {

}

void UIntegerInterval::mergeWith(UIntegerInterval interval) const {

}

Memento UIntegerInterval::getMemento() const {

}

void UIntegerInterval::restore(::model::saveable::Memento memento) {

}

Saveable::sptr UIntegerInterval::getDummy() {

}

}  // namespace model