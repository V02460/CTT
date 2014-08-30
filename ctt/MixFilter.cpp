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

QList<const Module*> MixFilter::getUsesList() const {
    throw new NotImplementedException();
}

bool MixFilter::uses(const Module &module) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model