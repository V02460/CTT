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

QString RGBChannelFilter::getName() const {
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

Saveable::sptr RGBChannelFilter::getDummy() {
    throw new NotImplementedException();
}

Saveable::SaveableType RGBChannelFilter::getType() const {
	return Saveable::SaveableType::rGBChannelFilter;
}

}  // namespace filter
}  // namespace model