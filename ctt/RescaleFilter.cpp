#include "RescaleFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

RescaleFilter::RescaleFilter(Module::sptr predecessor) : Filter(predecessor) {

}

RescaleFilter::~RescaleFilter() {

}

QString RescaleFilter::getName() const {

}

model::frame::Frame::sptr RescaleFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model