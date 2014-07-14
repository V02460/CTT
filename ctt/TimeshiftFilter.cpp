#include "TimeshiftFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

TimeshiftFilter::TimeshiftFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

TimeshiftFilter::~TimeshiftFilter() {
    throw new NotImplementedException();
}

QString TimeshiftFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr TimeshiftFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model