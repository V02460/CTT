#include "MixFilter.h"

#include "GPUSurfaceShader.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUSurfaceShader;

const QByteArray MixFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_mix");

const QString MixFilter::kParamMixRatioStr = QT_TR_NOOP("filter_mix_param_mixRatio");

MixFilter::MixFilter(Module::sptr module1, Module::sptr module2) : Filter(module1), module2(module2) {
    if (module1->getResolution() != module2->getResolution()) {
        throw new IllegalArgumentException("Resolution of the two Modules does not match.");
}

    newParameter(kParamMixRatioStr, 0.5f);
}

MixFilter::~MixFilter() {
}

Frame::sptr MixFilter::getFrame(unsigned int frameNumber) const {
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
    Memento memento = Filter::getMemento();
    
   memento.setFloat(kParamMixRatioStr, getParamValue<float>(kParamMixRatioStr));
   memento.setSharedPointer("module2", module2);

    return memento;
}

void MixFilter::restore(Memento memento) {
    Filter::restore(memento);

    setParam(FilterParam(kParamMixRatioStr, memento.getFloat(kParamMixRatioStr)));
    module2 = memento.getSharedPointer("module2").dynamicCast<Module>();
}

QList<const Module*> MixFilter::getUsesList() const {
    throw new NotImplementedException();
}

bool MixFilter::uses(const Module &module) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model