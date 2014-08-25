#include "NoiseFilter.h"

#include "NotImplementedException.h"
#include "GPUHelper.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUHelper;

const QString NoiseFilter::kParamIntensityStr = "filter_noise_param_intensity";

NoiseFilter::NoiseFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamIntensityStr, 0.5f);
}

NoiseFilter::~NoiseFilter() {
}

model::frame::Frame::sptr NoiseFilter::getFrame(unsigned int frameNumber) const {
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUHelper gpuHelper(":/Shader/Filter/Noise.fs", frame->getContext());

    gpuHelper.setValue("intensity", getParamValue<float>(kParamIntensityStr));
    gpuHelper.setValue("time", static_cast<GLfloat>(frameNumber));

    Surface::sptr targetSurface = gpuHelper.run(*frame.data());

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Memento NoiseFilter::getMemento() const {
    Memento memento = Filter::getMemento();

    memento.setFloat(kParamIntensityStr, getParamValue<float>(kParamIntensityStr));

    return memento;
}

void NoiseFilter::restore(Memento memento) {
    Filter::restore(memento);

    setParam(FilterParam(kParamIntensityStr, memento.getFloat(kParamIntensityStr)));
}

QList<const Module*> NoiseFilter::getUsesList() const {
    throw new NotImplementedException();
}

bool NoiseFilter::uses(const Module &module) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model