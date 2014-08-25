#include "RescaleFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

RescaleFilter::RescaleFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

RescaleFilter::~RescaleFilter() {
    throw new NotImplementedException();
}

QString RescaleFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr RescaleFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType RescaleFilter::getSaveableType() {
    return SaveableType::rescaleFilter;
}

}  // namespace filter
}  // namespace model