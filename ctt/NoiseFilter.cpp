#include "NoiseFilter.h"

#include "GPUHelper.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUHelper;
using ::model::saveable::Saveable;

NoiseFilter::NoiseFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamIntensityStr, 0.5f);
}

NoiseFilter::~NoiseFilter() {
}

model::frame::Frame::sptr NoiseFilter::getFrame(unsigned int frameNumber) const {
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUHelper gpuHelper(":/Shader/Filter/Noise.fs", frame->getContext());

    gpuHelper.setValue("intensity", getParamValue<float>(kParamIntensityStr));

    Surface::sptr targetSurface = gpuHelper.run(*frame.data());

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Saveable::SaveableType NoiseFilter::getType() const {
	return Saveable::SaveableType::noiseFilter;
}

const QString NoiseFilter::kParamIntensityStr = "filter_noise_param_intensity";

}  // namespace filter
}  // namespace model