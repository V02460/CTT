#include "MixFilter.h"

#include "GPUSurfaceShader.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::exception::AccessToDummyException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUSurfaceShader;

const QByteArray MixFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_mix");

const QByteArray MixFilter::kParamMixRatioStr = QT_TRANSLATE_NOOP("Param", "filter_mix_param_mixRatio");

MixFilter::MixFilter(Module::sptr module1, Module::sptr module2) : Filter(module1), module2(module2) {
    if (module1->getResolution() != module2->getResolution()) {
        throw IllegalArgumentException("Resolution of the two Modules does not match.");
    }

    newParameter(kParamMixRatioStr, 0.5f);
}

MixFilter::MixFilter() {
	isDummyFlag = true;
}

MixFilter::~MixFilter() {
}

Frame::sptr MixFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
     Frame::sptr frame1 = getPredecessor()->getFrame(frameNumber);
     Frame::sptr frame2 = module2->getFrame(frameNumber);

     GPUSurfaceShader gpuHelper(":/Shader/Filter/Mix.fs", frame1.staticCast<Surface>());

     gpuHelper.setValue("sourceTexture2", frame2.staticCast<Surface>());

     float mixRatio = getParamValue<float>(kParamMixRatioStr);
     mixRatio = qBound(0.f, mixRatio, 1.f);
     gpuHelper.setValue("mixRatio", mixRatio);

     Surface::sptr mixed = gpuHelper.run();

     return Frame::sptr(new Frame(mixed, FrameMetadata(mixed->getSize())));
}

Memento MixFilter::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    Memento memento = Filter::getMemento();
    
   memento.setFloat(kParamMixRatioStr, getParamValue<float>(kParamMixRatioStr));
   memento.setSharedPointer("module2", module2);

    return memento;
}

void MixFilter::restore(Memento memento) {
    Filter::restore(memento);
    
    newParameter(kParamMixRatioStr, memento.getFloat(kParamMixRatioStr));
    module2 = memento.getSharedPointer("module2").dynamicCast<Module>();
}

QList<const Module*> MixFilter::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return QList<const Module*>() << this
		                          << module2.data(); // TODO
}

Saveable::sptr MixFilter::getDummy() {
	return MixFilter::sptr(new MixFilter());
}

}  // namespace filter
}  // namespace model