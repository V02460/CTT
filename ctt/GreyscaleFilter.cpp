#include "GreyscaleFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

GreyscaleFilter::GreyscaleFilter(Module::sptr predecessor) : Filter(predecessor) {

}

GreyscaleFilter::~GreyscaleFilter() {

}

QString GreyscaleFilter::getName() const {

}

Frame GreyscaleFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model