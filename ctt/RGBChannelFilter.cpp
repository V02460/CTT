#include "RGBChannelFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;

RGBChannelFilter::RGBChannelFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

RGBChannelFilter::~RGBChannelFilter() {
    throw new NotImplementedException();
}

model::frame::Frame::sptr RGBChannelFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Memento RGBChannelFilter::getMemento() const {
    throw new NotImplementedException();
}

void RGBChannelFilter::restore(Memento memento) {
    throw new NotImplementedException();
}

QList<const Module*> RGBChannelFilter::getUsesList() const {
    return QList<const Module*>() << this;
}

Saveable::sptr RGBChannelFilter::getDummy() {
    throw new NotImplementedException();
}

Saveable::SaveableType RGBChannelFilter::getSaveableType() {
    return SaveableType::rGBChannelFilter;
}

}  // namespace filter
}  // namespace model