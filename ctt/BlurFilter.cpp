#include "BlurFilter.h"

#include "GPUHelper.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUHelper;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

BlurFilter::BlurFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamRadiusStr, 5.f);
}

BlurFilter::~BlurFilter() {

}

model::frame::Frame::sptr BlurFilter::getFrame(unsigned int frameNumber) const {

    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUHelper gpuHelper(":/Shader/Filter/1DBlur.fs", frame->getContext());

    gpuHelper.setValue("radius", getParamValue<float>(kParamRadiusStr));

    // horizontal blur
    gpuHelper.setValue("direction", QVector2D(1.f, 0.f));
    Surface::sptr targetSurface = gpuHelper.run(*frame.data());

    // vertical blur
    gpuHelper.setValue("direction", QVector2D(0.f, 1.f));
    targetSurface = gpuHelper.run(*targetSurface.data());

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Saveable::SaveableType BlurFilter::getType() const {
	return Saveable::SaveableType::blurFilter;
}

Memento BlurFilter::getMemento() const {
    return Filter::getMemento();
}

void BlurFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> BlurFilter::getUsesList() const {
    return QList<const Module*>() << this;
}

const QString BlurFilter::kParamRadiusStr = "filter_blur_param_radius";

}  // namespace filter
}  // namespace model