#include "TimeshiftFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::NotImplementedException;

TimeshiftFilter::TimeshiftFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamShiftStr, 0);
}

TimeshiftFilter::~TimeshiftFilter() {
}

model::frame::Frame::sptr TimeshiftFilter::getFrame(unsigned int frameNumber) const {
    int shift = getParamValue<int>(kParamShiftStr);
    return getPredecessor()->getFrame(frameNumber + shift);
}

Memento TimeshiftFilter::getMemento() const {
    throw new NotImplementedException();
}

void TimeshiftFilter::restore(Memento memento) {
    throw new NotImplementedException();
}

QList<const Module*> TimeshiftFilter::getUsesList() const {
    return QList<const Module*>() << this;
}

Saveable::sptr TimeshiftFilter::getDummy() {
    throw new NotImplementedException();
}
Saveable::SaveableType TimeshiftFilter::getSaveableType() {
    return SaveableType::timeshiftFilter;
}

const QString TimeshiftFilter::kParamShiftStr = "filter_timeshift_param_shift";

}  // namespace filter
}  // namespace model