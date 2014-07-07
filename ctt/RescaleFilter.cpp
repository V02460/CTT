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

Frame RescaleFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model