#include "NoiseFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

NoiseFilter::NoiseFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

NoiseFilter::~NoiseFilter() {
    throw new NotImplementedException();
}

QString NoiseFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr NoiseFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model