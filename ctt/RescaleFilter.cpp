#include "RescaleFilter.h"

#include "GPUSurfaceShader.h"
#include "FilterParam.h"
#include "FrameMetadata.h"

#include "NotImplementedException.h"
#include "AccessToDummyException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::model::filter::FilterParam;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUSurfaceShader;
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;

const QByteArray RescaleFilter::kFilterID = QT_TRANSLATE_NOOP("Filter", "filter_rescale");

const QByteArray RescaleFilter::kParamNewSizeWidth = QT_TRANSLATE_NOOP("Param", "filter_rescale_param_newsize_width");
const QByteArray RescaleFilter::kParamNewSizeHeight = QT_TRANSLATE_NOOP("Param", "filter_rescale_param_newsize_height");

RescaleFilter::RescaleFilter(Module::sptr predecessor) : Filter(predecessor) {
    QSize resolution = predecessor->getResolution();
    newParameter(kParamNewSizeWidth, static_cast<unsigned int>(resolution.width()));
    newParameter(kParamNewSizeHeight, static_cast<unsigned int>(resolution.height()));
}

RescaleFilter::RescaleFilter() {
	isDummyFlag = true;
}

RescaleFilter::~RescaleFilter() {}

model::frame::Frame::sptr RescaleFilter::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    Frame::sptr sourceFrame = getPredecessor()->getFrame(frameNumber);

    QSize newSize(getParamValue<unsigned int>(kParamNewSizeWidth), 
                  getParamValue<unsigned int>(kParamNewSizeHeight));

    if (newSize.width() < 1) {
        newSize.setWidth(1);
    }
    if (newSize.height() < 1) {
        newSize.setHeight(1);
    }

    GPUSurfaceShader gpuHelper(":/Shader/Filter/Rescale.fs", sourceFrame.staticCast<Surface>());

    Surface::sptr targetSurface = gpuHelper.run(newSize);

    return Frame::sptr(new Frame(targetSurface, FrameMetadata(targetSurface->getSize())));
}

Memento RescaleFilter::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    Memento memento = Filter::getMemento();

    QSize newSize(getParamValue<unsigned int>(kParamNewSizeWidth),
                  getParamValue<unsigned int>(kParamNewSizeHeight));

    memento.setInt(kParamNewSizeWidth, newSize.width());
    memento.setInt(kParamNewSizeHeight, newSize.height());

    return memento;
}

void RescaleFilter::restore(Memento memento) {
    Filter::restore(memento);

    newParameter(kParamNewSizeWidth, memento.getUInt(kParamNewSizeWidth));
    newParameter(kParamNewSizeHeight, memento.getUInt(kParamNewSizeHeight));
}

QList<const Module*> RescaleFilter::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return QList<const Module*>() << this;
}
Saveable::sptr RescaleFilter::getDummy() {
	return RescaleFilter::sptr(new RescaleFilter());
}

}  // namespace filter
}  // namespace model