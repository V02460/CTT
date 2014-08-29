#include "RescaleFilter.h"

#include "NotImplementedException.h"
#include "GPUHelper.h"
#include "FilterParam.h"
#include "FrameMetadata.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::model::filter::FilterParam;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUHelper;
using ::exception::NotImplementedException;

const QString RescaleFilter::kParamNewSize = "filter_rescale_param_newsize";
const QString RescaleFilter::kParamNewSizeWidth = "filter_rescale_param_newsize_width";
const QString RescaleFilter::kParamNewSizeHeight = "filter_rescale_param_newsize_height";

RescaleFilter::RescaleFilter(Module::sptr predecessor) : Filter(predecessor) {
    newParameter(kParamNewSize, predecessor->getResolution());
}

RescaleFilter::~RescaleFilter() {
}

model::frame::Frame::sptr RescaleFilter::getFrame(unsigned int frameNumber) const {
    Frame::sptr sourceFrame = getPredecessor()->getFrame(frameNumber);

    QSize newSize = getParamValue<QSize>(kParamNewSize);

    if (newSize.width() < 1) {
        newSize.setWidth(1);
    }
    if (newSize.height() < 1) {
        newSize.setHeight(1);
}

    GPUHelper gpuHelper(":/Shader/Filter/Rescale.fs", sourceFrame->getContext());

    Surface::sptr targetSurface = gpuHelper.run(*sourceFrame.data(), newSize);

    return Frame::sptr(new Frame(targetSurface, FrameMetadata(targetSurface->getSize())));
}

Memento RescaleFilter::getMemento() const {
    Memento memento = Filter::getMemento();

    QSize newSize = getParamValue<QSize>(kParamNewSize);

    memento.setInt(kParamNewSizeWidth, newSize.width());
    memento.setInt(kParamNewSizeHeight, newSize.height());

    return memento;
}

void RescaleFilter::restore(Memento memento) {
    Filter::restore(memento);

    QSize newSize;
    newSize.setWidth(memento.getInt(kParamNewSizeWidth));
    newSize.setWidth(memento.getInt(kParamNewSizeHeight));
    setParam(FilterParam::sptr(new FilterParam(kParamNewSize, newSize)));
}

QList<const Module*> RescaleFilter::getUsesList() const {
    throw new NotImplementedException();
}

bool RescaleFilter::uses(const ::model::Module &module) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model