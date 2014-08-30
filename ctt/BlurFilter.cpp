#include "BlurFilter.h"

#include "GPUSurfaceShader.h"

#include "AccessToDummyException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUSurfaceShader;
using ::model::saveable::Saveable;

BlurFilter::BlurFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamRadiusStr, 5.f);
}

BlurFilter::~BlurFilter() {
}

model::frame::Frame::sptr BlurFilter::getFrame(unsigned int frameNumber) const {

    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUSurfaceShader gpuHelper(":/Shader/Filter/1DBlur.fs", frame->getContext());

    gpuHelper.setValue("radius", getParamValue<float>(kParamRadiusStr));

    // horizontal blur
    gpuHelper.setValue("direction", QVector2D(1.f, 0.f));
    gpuHelper.setSourceTexture(frame);
    Surface::sptr targetSurface = gpuHelper.run();

    // vertical blur
    gpuHelper.setValue("direction", QVector2D(0.f, 1.f));
    gpuHelper.setSourceTexture(targetSurface);
    targetSurface = gpuHelper.run();

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Saveable::SaveableType BlurFilter::getType() const {
	return Saveable::SaveableType::blurFilter;
}

const QString BlurFilter::kParamRadiusStr = "filter_blur_param_radius";

}  // namespace filter
}  // namespace model