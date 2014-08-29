#include "TimeshiftFilter.h"

#include "MathHelper.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::clamp;
using ::exception::NotImplementedException;

const QByteArray TimeshiftFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_timeshift");

const QString TimeshiftFilter::kParamShiftStr = QT_TR_NOOP("filter_timeshift_param_shift");

TimeshiftFilter::TimeshiftFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamShiftStr, 0);
}

TimeshiftFilter::~TimeshiftFilter() {
}

model::frame::Frame::sptr TimeshiftFilter::getFrame(unsigned int frameNumber) const {
    int shift = getParamValue<int>(kParamShiftStr);

    Module *predecessor = getPredecessor();

    unsigned int newFrameNumber = clamp(static_cast<int>(frameNumber)+shift,
                                        0,
                                        static_cast<int>(predecessor->getFrameCount()) - 1);
    

    return predecessor->getFrame(newFrameNumber);
}

Memento TimeshiftFilter::getMemento() const {
    throw new NotImplementedException();
}

void TimeshiftFilter::restore(Memento memento) {
    throw new NotImplementedException();
}

QList<const Module*> TimeshiftFilter::getUsesList() const {
    throw new NotImplementedException();
}

bool TimeshiftFilter::uses(const ::model::Module &module) const {
    throw new NotImplementedException();
}

Saveable::sptr TimeshiftFilter::getDummy() {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model