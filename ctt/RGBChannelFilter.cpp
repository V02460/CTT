#include "RGBChannelFilter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

RGBChannelFilter::RGBChannelFilter(Module::sptr predecessor) : Filter(predecessor) {

}

bool RGBChannelFilter::supportsIntervals() const {

}

QString RGBChannelFilter::getName() const {

}

Frame RGBChannelFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model