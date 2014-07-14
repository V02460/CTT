#include "GreyscaleFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

GreyscaleFilter::GreyscaleFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

GreyscaleFilter::~GreyscaleFilter() {
    throw new NotImplementedException();
}

QString GreyscaleFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr GreyscaleFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model