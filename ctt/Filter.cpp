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

Filter::Filter(Module::sptr predecessor) : predecessor(predecessor), parameters(), intervals() {}

Filter::~Filter() {}

QList<FilterParam::sptr> Filter::getParams() const {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    return parameters.values();
}

void Filter::setParam(FilterParam::sptr parameter) {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    if (!parameters.contains(parameter->getName())) {
        throw IllegalArgumentException("Parameter '" + parameter->getName() + "' must exist in Filter to be set.");
    }

    QVariant oldValue = parameters.value(parameter->getName(), parameter)->getValue();
    QVariant newValue = parameter->getValue();
    
    if (newValue.type() != oldValue.type()) {
        throw IllegalArgumentException("Variable type of FilterParam does not match stored type.");
    }

    parameters.insert(parameter->getName(), parameter);
    changed();
}

void Filter::setPreviousModule(Module::sptr predecessor) {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    if (predecessor.isNull()) {
        throw IllegalArgumentException("Predecessor must not be null.");
    }
    this->predecessor = predecessor;
}

void Filter::activate(UIntegerInterval::sptr interval) {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    intervals->activate(interval);
}

void Filter::deactivate(UIntegerInterval::sptr interval) {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    intervals->deactivate(interval);
}

QList<UIntegerInterval::sptr> Filter::getListOfActiveIntervals() {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    return intervals->getIntervalList();
}

unsigned int Filter::getFrameCount() const {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    return predecessor->getFrameCount();
}

Module *Filter::getPredecessor() const {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    return predecessor.data();
}

Filter::Filter() {
    isDummyFlag = true;
}

QSize Filter::getResolution() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return predecessor->getResolution();
}

Memento Filter::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	Memento memento;
    memento.setSharedPointer("predecessor", predecessor);
	memento.setSharedPointer("intervals", intervals);
    return memento;
}

void Filter::restore(Memento memento) {
    predecessor = memento.getSharedPointer("predecessor").dynamicCast<Module>();
	intervals = memento.getSharedPointer("intervals").dynamicCast<FilterIntervalList>();
}

QList<const Module*> Filter::getUsesList() const {
    return Module::getUsesList();
}

}  // namespace filter
}  // namespace model