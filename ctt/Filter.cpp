#include "Filter.h"

#include "IllegalArgumentException.h"
#include "AccessToDummyException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::Module;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::AccessToDummyException;
using ::exception::IllegalArgumentException;
using ::exception::IllegalStateException;

Filter::Filter(Module::sptr predecessor) : predecessor(predecessor), parameters(), intervals() {
}

Filter::~Filter() {
}

QList<FilterParam::sptr> Filter::getParams() const {
    if (isDummy()) {
        throw new AccessToDummyException();
    }

    return parameters.values();
}

void Filter::setParam(FilterParam::sptr parameter) {
    if (isDummy()) {
        throw new AccessToDummyException();
    }
    if (!parameters.contains(parameter->getName())) {
        throw new IllegalArgumentException("Parameter '" + parameter->getName() + "' must exist in Filter to be set.");
    }

    QVariant oldValue = parameters.value(parameter->getName(), parameter)->getValue();
    QVariant newValue = parameter->getValue();

    if (newValue.type() != oldValue.type()) {
        throw new IllegalArgumentException("Variable type of FilterParam does not match stored type.");
    }

    parameters.insert(parameter->getName(), parameter);
}

void Filter::setPreviousModule(Module::sptr predecessor) {
    if (isDummy()) {
        throw new AccessToDummyException();
    }
    if (predecessor.isNull()) {
        throw new IllegalArgumentException("Predecessor must not be null.");
    }

    this->predecessor = predecessor;
}

void Filter::activate(UIntegerInterval interval) {
    if (isDummy()) {
        throw new AccessToDummyException();
    }

    intervals.activate(interval);
}

void Filter::deactivate(UIntegerInterval interval) {
    if (isDummy()) {
        throw new AccessToDummyException();
    }

    intervals.deactivate(interval);
}

QList<UIntegerInterval> Filter::getListOfActiveIntervals() {
    if (isDummy()) {
        throw new AccessToDummyException();
    }

    return intervals.getIntervalList();
}

unsigned int Filter::getFrameCount() const {
    if (isDummy()) {
        throw new AccessToDummyException();
    }

    return predecessor->getFrameCount();
}

Module *Filter::getPredecessor() const {
    if (isDummy()) {
        throw new AccessToDummyException();
    }

    return predecessor.data();
}

QSize Filter::getResolution() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the resolution of a dummy Filter.");
	}

	return predecessor->getResolution();
}

Memento Filter::getMemento() const {
    Memento memento;
    memento.setSharedPointer("predecessor", predecessor);
    return memento;
}

// TODO isDummyFlag = false ... nicht mehr zu restoren? Doch!!!
void Filter::restore(Memento memento) {
    predecessor = memento.getSharedPointer("predecessor").dynamicCast<Module>();
}

}  // namespace filter
}  // namespace model