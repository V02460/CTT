#include "GreyscaleFilter.h"

#include "GPUHelper.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Saveable;
using ::helper::GPUHelper;

GreyscaleFilter::GreyscaleFilter(Module::sptr predecessor) : Filter(predecessor) {
}

GreyscaleFilter::~GreyscaleFilter() {
}

Frame::sptr GreyscaleFilter::getFrame(unsigned int frameNumber) const {
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUHelper gpuHelper(":/Shader/Filter/Greyscale.fs", frame->getContext());

    Surface::sptr targetSurface = gpuHelper.run(*frame.data());

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Saveable::SaveableType GreyscaleFilter::getType() const {
	return Saveable::SaveableType::greyscaleFilter;
}

}  // namespace filter
}  // namespace model