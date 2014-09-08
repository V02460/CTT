#include "NoiseFilter.h"

#include "NotImplementedException.h"
#include "GPUSurfaceShader.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::AccessToDummyException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUSurfaceShader;

const QByteArray NoiseFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_noise");

const QString NoiseFilter::kParamIntensityStr = QT_TR_NOOP("filter_noise_param_intensity");

NoiseFilter::NoiseFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamIntensityStr, 0.5f);
}

NoiseFilter::NoiseFilter() {
	isDummyFlag = true;
}

NoiseFilter::~NoiseFilter() {}

model::frame::Frame::sptr NoiseFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUSurfaceShader gpuHelper(":/Shader/Filter/Noise.fs", frame.staticCast<Surface>());

    float intensity = getParamValue<float>(kParamIntensityStr);
    intensity = qBound(0.f, intensity, 1.f);
    gpuHelper.setValue("intensity", intensity);
    gpuHelper.setValue("time", static_cast<GLfloat>(frameNumber));

    Surface::sptr targetSurface = gpuHelper.run();

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Memento NoiseFilter::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    Memento memento = Filter::getMemento();

    memento.setFloat(kParamIntensityStr, getParamValue<float>(kParamIntensityStr));

    return memento;
}

void NoiseFilter::restore(Memento memento) {
    Filter::restore(memento);

    newParameter(kParamIntensityStr, memento.getFloat(kParamIntensityStr));
}

QList<const Module*> NoiseFilter::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return QList<const Module*>() << this;
}

Saveable::sptr NoiseFilter::getDummy() {
	return NoiseFilter::sptr(new NoiseFilter());
}

}  // namespace filter
}  // namespace model