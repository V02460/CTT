#include "TimeshiftFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

TimeshiftFilter::TimeshiftFilter(Module::sptr predecessor) : Filter(predecessor) {

}

TimeshiftFilter::~TimeshiftFilter() {

}

QString TimeshiftFilter::getName() const {

}

model::frame::Frame::sptr TimeshiftFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model