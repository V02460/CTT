#include "RescaleFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

RescaleFilter::RescaleFilter(Module::sptr predecessor) : Filter(predecessor) {

}

bool RescaleFilter::supportsIntervals() const {

}

QString RescaleFilter::getName() const {

}

Frame RescaleFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model