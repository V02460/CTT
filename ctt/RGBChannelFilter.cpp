#include "RGBChannelFilter.h"

#include "GPUSurfaceShader.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::helper::GPUSurfaceShader;
using ::exception::AccessToDummyException;

const QByteArray RGBChannelFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_rgbchannel");

const QByteArray RGBChannelFilter::kParamRedStr = QT_TRANSLATE_NOOP("Param", "filter_rgbchannel_param_red");
const QByteArray RGBChannelFilter::kParamGreenStr = QT_TRANSLATE_NOOP("Param", "filter_rgbchannel_param_green");
const QByteArray RGBChannelFilter::kParamBlueStr = QT_TRANSLATE_NOOP("Param", "filter_rgbchannel_param_blue");

RGBChannelFilter::RGBChannelFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamRedStr, 100);
    newParameter(kParamGreenStr, 100);
    newParameter(kParamBlueStr, 100);
}

RGBChannelFilter::RGBChannelFilter() {
	isDummyFlag = true;
}

RGBChannelFilter::~RGBChannelFilter() {}

model::frame::Frame::sptr RGBChannelFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUSurfaceShader gpuHelper(":/Shader/Filter/RGBChannel.fs", frame.staticCast<Surface>());

    float red = getParamValue<float>(kParamRedStr) / 100.f;
    red = qBound(0.f, red, 1.f);
    float green = getParamValue<float>(kParamGreenStr) / 100;
    green = qBound(0.f, green, 1.f);
    float blue = getParamValue<float>(kParamBlueStr) / 100;
    blue = qBound(0.f, blue, 1.f);

    gpuHelper.setValue("colorFactor", QVector4D(red, green, blue, 1.f));

    Surface::sptr targetSurface = gpuHelper.run();

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Memento RGBChannelFilter::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    Memento memento = Filter::getMemento();

    memento.setInt(kParamRedStr, getParamValue<int>(kParamRedStr));
    memento.setInt(kParamGreenStr, getParamValue<int>(kParamGreenStr));
    memento.setInt(kParamBlueStr, getParamValue<int>(kParamBlueStr));

    return memento;
}

void RGBChannelFilter::restore(Memento memento) {
    Filter::restore(memento);

    newParameter(kParamRedStr, memento.getInt(kParamRedStr));
    newParameter(kParamGreenStr, memento.getInt(kParamGreenStr));
    newParameter(kParamBlueStr, memento.getInt(kParamBlueStr));
}

QList<const Module*> RGBChannelFilter::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
}
	return QList<const Module*>() << this;
}

Saveable::sptr RGBChannelFilter::getDummy() {
	return RGBChannelFilter::sptr(new RGBChannelFilter());
}

}  // namespace filter
}  // namespace model