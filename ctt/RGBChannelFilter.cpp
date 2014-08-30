#include "RGBChannelFilter.h"

#include "GPUHelper.h"
#include "MathHelper.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::helper::GPUHelper;
using ::helper::clamp;
using ::exception::NotImplementedException;

const QByteArray RGBChannelFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_rgbchannel");

const QString RGBChannelFilter::kParamRedStr = QT_TR_NOOP("filter_rgbchannel_param_red");
const QString RGBChannelFilter::kParamGreenStr = QT_TR_NOOP("filter_rgbchannel_param_green");
const QString RGBChannelFilter::kParamBlueStr = QT_TR_NOOP("filter_rgbchannel_param_blue");

RGBChannelFilter::RGBChannelFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamRedStr, 100);
    newParameter(kParamGreenStr, 100);
    newParameter(kParamBlueStr, 100);
}

RGBChannelFilter::~RGBChannelFilter() {
}

model::frame::Frame::sptr RGBChannelFilter::getFrame(unsigned int frameNumber) const {
    Frame::sptr frame = getPredecessor()->getFrame(frameNumber);

    GPUHelper gpuHelper(":/Shader/Filter/RGBChannel.fs", frame->getContext());

    float red = getParamValue<float>(kParamRedStr) / 100.f;
    red = clamp(red, 0.f, 1.f);
    float green = getParamValue<float>(kParamGreenStr) / 100;
    green = clamp(green, 0.f, 1.f);
    float blue = getParamValue<float>(kParamBlueStr) / 100;
    blue = clamp(blue, 0.f, 1.f);

    gpuHelper.setValue("colorFactor", QVector4D(red, green, blue, 1.f));

    Surface::sptr targetSurface = gpuHelper.run(*frame.data());

    return Frame::sptr(new Frame(targetSurface, frame->getMetadata()));
}

Memento RGBChannelFilter::getMemento() const {
    Memento memento = Filter::getMemento();

    memento.setInt(kParamRedStr, getParamValue<int>(kParamRedStr));
    memento.setInt(kParamGreenStr, getParamValue<int>(kParamGreenStr));
    memento.setInt(kParamBlueStr, getParamValue<int>(kParamBlueStr));

    return memento;
}

void RGBChannelFilter::restore(Memento memento) {
    Filter::restore(memento);

	setParam(FilterParam::sptr(new FilterParam(kParamRedStr, memento.getInt(kParamRedStr))));
	setParam(FilterParam::sptr(new FilterParam(kParamGreenStr, memento.getInt(kParamGreenStr))));
	setParam(FilterParam::sptr(new FilterParam(kParamBlueStr, memento.getInt(kParamBlueStr))));
}

QList<const Module*> RGBChannelFilter::getUsesList() const {
    throw new NotImplementedException();
}

bool RGBChannelFilter::uses(const model::Module &module) const {
    throw new NotImplementedException();
}

Saveable::sptr RGBChannelFilter::getDummy() {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model