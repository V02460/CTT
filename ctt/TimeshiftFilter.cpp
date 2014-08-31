#include "TimeshiftFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;
using ::exception::NotImplementedException;

const QByteArray TimeshiftFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_timeshift");

const QString TimeshiftFilter::kParamShiftStr = QT_TR_NOOP("filter_timeshift_param_shift");

TimeshiftFilter::TimeshiftFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamShiftStr, 0);
}

TimeshiftFilter::TimeshiftFilter() {
	isDummyFlag = true;
}

TimeshiftFilter::~TimeshiftFilter() {}

model::frame::Frame::sptr TimeshiftFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    int shift = getParamValue<int>(kParamShiftStr);

    Module *predecessor = getPredecessor();

    unsigned int newFrameNumber = qBound(0,
                                         static_cast<int>(frameNumber) + shift,
                                        static_cast<int>(predecessor->getFrameCount()) - 1);
    

    return predecessor->getFrame(newFrameNumber);
}

Memento TimeshiftFilter::getMemento() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	return Filter::getMemento();
}

void TimeshiftFilter::restore(Memento memento) {
	if (isDummy()) {
		throw new AccessToDummyException();
}
	Filter::restore(memento);
	isDummyFlag = false;
}

QList<const Module*> TimeshiftFilter::getUsesList() const {
	return QList<const Module*>() << this;
}

Saveable::sptr TimeshiftFilter::getDummy() {
	return TimeshiftFilter::sptr(new TimeshiftFilter());
}

}  // namespace filter
}  // namespace model