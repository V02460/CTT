#include "RGBChannelFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;

RGBChannelFilter::RGBChannelFilter(Module::sptr predecessor) : Filter(predecessor) {

}

RGBChannelFilter::~RGBChannelFilter() {

}

QString RGBChannelFilter::getName() const {

}

Frame RGBChannelFilter::getFrame(unsigned int frameNumber) const {

}

Memento RGBChannelFilter::getMemento() const {

}

void RGBChannelFilter::restore(Memento memento) {

}

Saveable::sptr RGBChannelFilter::getDummy() {

}

}  // namespace filter
}  // namespace model