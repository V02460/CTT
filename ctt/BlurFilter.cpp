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
using ::exception::AccessToDummyException;

const QByteArray BlurFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_blur");

const QString BlurFilter::kParamRadiusStr = QT_TR_NOOP("filter_blur_param_radius");

BlurFilter::BlurFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamRadiusStr, 5.f);
}

BlurFilter::~BlurFilter() {}

model::frame::Frame::sptr BlurFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}

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
	if (isDummy()) {
		throw AccessToDummyException();
	}

    Memento memento = Filter::getMemento();
    memento.setFloat(kParamRadiusStr, getParamValue<float>(kParamRadiusStr));
    return memento;
}

void BlurFilter::restore(Memento memento) {
	Filter::restore(memento);
    newParameter(kParamRadiusStr, memento.getFloat(kParamRadiusStr));
}

QList<const Module*> BlurFilter::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return QList<const Module*>() << this;
}

Saveable::sptr BlurFilter::getDummy() {
	return BlurFilter::sptr(new BlurFilter());
}

BlurFilter::BlurFilter() {
    isDummyFlag = true;
}

}  // namespace filter
}  // namespace model