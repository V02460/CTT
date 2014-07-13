#include "Filter.h"

#include "IllegalArgumentException.h"
#include "AccessToDummyException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::Module;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;
using ::exception::IllegalArgumentException;

Filter::Filter(Module::sptr predecessor) : predecessor(predecessor), parameters(), intervals() {
}

Filter::~Filter() {

}

QList<FilterParam> Filter::getParams() const {
    if (isDummy()) {
        throw new AccessToDummyException();
    }

    return parameters.values();
}

void Filter::setParam(FilterParam parameter) {
    if (isDummy()) {
        throw new AccessToDummyException();
    }

    parameters.insert(parameter.getName(), parameter);
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

    predecessor->getFrameCount();
}

}  // namespace filter
}  // namespace model