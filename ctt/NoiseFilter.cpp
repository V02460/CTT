#include "NoiseFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

NoiseFilter::NoiseFilter(Module::sptr predecessor) : Filter(predecessor) {

}

NoiseFilter::~NoiseFilter() {

}

QString NoiseFilter::getName() const {

}

model::frame::Frame::sptr NoiseFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model