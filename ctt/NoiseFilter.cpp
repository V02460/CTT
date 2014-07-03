#include "NoiseFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

NoiseFilter::NoiseFilter(Module::sptr predecessor) : Filter(predecessor) {

}

bool NoiseFilter::supportsIntervals() const {

}

QString NoiseFilter::getName() const {

}

Frame NoiseFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model