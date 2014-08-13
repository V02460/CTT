#include "TimeshiftFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

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

Saveable::SaveableType TimeshiftFilter::getType() const {
	return Saveable::SaveableType::timeshiftFilter;
}

}  // namespace filter
}  // namespace model