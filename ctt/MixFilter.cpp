#include "MixFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

MixFilter::MixFilter(Module::sptr predecessor, Surface::sptr surface) : Filter(predecessor) {
    throw new NotImplementedException();
}

MixFilter::~MixFilter() {
    throw new NotImplementedException();
}

QString MixFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr MixFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model