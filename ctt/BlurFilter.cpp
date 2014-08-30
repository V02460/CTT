#include "BlurFilter.h"

#include "GPUSurfaceShader.h"

#include "AccessToDummyException.h"
#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::helper::GPUSurfaceShader;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::NotImplementedException;

const QByteArray BlurFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_blur");

const QString BlurFilter::kParamRadiusStr = QT_TR_NOOP("filter_blur_param_radius");

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

Memento BlurFilter::getMemento() const {
    return Filter::getMemento();
}

void BlurFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> BlurFilter::getUsesList() const {
    throw new NotImplementedException();
}

bool BlurFilter::uses(const model::Module &module) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model