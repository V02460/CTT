#include "MixFilter.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

MixFilter::MixFilter(Module::sptr predecessor, Surface::sptr surface) : Filter(predecessor) {

}

MixFilter::~MixFilter() {

}

QString MixFilter::getName() const {

}

Frame MixFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model