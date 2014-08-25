#include "NoiseFilter.h"

#include "GPUHelper.h"
#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUHelper;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::NotImplementedException;

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

QString NoiseFilter::getName() const {
	// TODO sorry
	throw new NotImplementedException();
}

Memento NoiseFilter::getMemento() const {
    return Filter::getMemento();
}

void NoiseFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> NoiseFilter::getUsesList() const {
    return QList<const Module*>() << this;
}

Saveable::SaveableType NoiseFilter::getSaveableType() {
    return SaveableType::noiseFilter;
}

const QString NoiseFilter::kParamIntensityStr = "filter_noise_param_intensity";

}  // namespace filter
}  // namespace model