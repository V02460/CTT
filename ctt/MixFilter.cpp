#include "MixFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

MixFilter::MixFilter(Module::sptr predecessor, Module::sptr module) : Filter(predecessor) {
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

Saveable::SaveableType MixFilter::getType() const {
    return Saveable::mixFilter;
}

}  // namespace filter
}  // namespace model