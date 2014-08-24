#include "TimeshiftFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Saveable;

TimeshiftFilter::TimeshiftFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamShiftStr, 0);
}

TimeshiftFilter::~TimeshiftFilter() {
}

model::frame::Frame::sptr TimeshiftFilter::getFrame(unsigned int frameNumber) const {
    int shift = getParamValue<int>(kParamShiftStr);
    return getPredecessor()->getFrame(frameNumber + shift);
}

const QString TimeshiftFilter::kParamShiftStr = "filter_timeshift_param_shift";

}  // namespace filter
}  // namespace model