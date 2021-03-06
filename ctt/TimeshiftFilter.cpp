#include "TimeshiftFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;

const QByteArray TimeshiftFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_timeshift");

const QByteArray TimeshiftFilter::kParamShiftStr = QT_TRANSLATE_NOOP("Param", "filter_timeshift_param_shift");

TimeshiftFilter::TimeshiftFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamShiftStr, 0);
}

TimeshiftFilter::TimeshiftFilter() {
	isDummyFlag = true;
}

TimeshiftFilter::~TimeshiftFilter() {}

model::frame::Frame::sptr TimeshiftFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
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
		throw AccessToDummyException();
	}

    Memento memento = Filter::getMemento();
    memento.setInt(kParamShiftStr, getParamValue<int>(kParamShiftStr));
	return memento;
}

void TimeshiftFilter::restore(Memento memento) {
	Filter::restore(memento);
	newParameter(kParamShiftStr, memento.getInt(kParamShiftStr));
}

QList<const Module*> TimeshiftFilter::getUsesList() const {
    if (isDummy()) {
        throw AccessToDummyException();
    }

	return QList<const Module*>() << this;
}

Saveable::sptr TimeshiftFilter::getDummy() {
	return TimeshiftFilter::sptr(new TimeshiftFilter());
}

}  // namespace filter
}  // namespace model