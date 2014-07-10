#include "Frame.h"

#include "RedHistogram.h"
#include "GreenHistogram.h"
#include "BlueHistogram.h"
#include "LuminanceHistogram.h"
#include "HueHistogram.h"
#include "SaturationHistogram.h"

namespace model {
namespace frame {

using ::model::frame::histogram::Histogram;
using ::model::frame::histogram::RedHistogram;
using ::model::frame::histogram::GreenHistogram;
using ::model::frame::histogram::BlueHistogram;
using ::model::frame::histogram::HueHistogram;
using ::model::frame::histogram::SaturationHistogram;
using ::model::frame::histogram::LuminanceHistogram;
using ::exception::IllegalArgumentException;

Frame::Frame(QSharedPointer<QOpenGLContext> context, QImage image, FrameMetadata metadata)
        : Surface(context, image.size())
        , metadata(metadata) {
	if (image.size() == metadata.getSize()) {
		throw new IllegalArgumentException("Tried to create a frame from an image of size " 
			+ QString(image.size().width()) + "*" + QString(image.size().height())
			+ " but the submitted metadata specified a size of " + QString(metadata.getSize().width()) + "*" 
			+ QString(metadata.getSize().height()) + ".");
	}
    glTexture.setData(image, QOpenGLTexture::DontGenerateMipMaps);
}

Frame::Frame(QSharedPointer<QOpenGLContext> context, FrameMetadata metadata)
        : Surface(context, metadata.getSize())
        , metadata(metadata) {

}

FrameMetadata Frame::getMetadata() const {
    return metadata;
}

Histogram::sptr Frame::getHistogram(Histogram::HistogramType type) const {
    switch (type)
    {
    case Histogram::Red:
        return Histogram::sptr(new RedHistogram(*this));
    case Histogram::Green:
        return Histogram::sptr(new GreenHistogram(*this));
    case Histogram::Blue:
        return Histogram::sptr(new BlueHistogram(*this));
    case Histogram::Luminance:
        return Histogram::sptr(new LuminanceHistogram(*this));
    case Histogram::Hue:
        return Histogram::sptr(new HueHistogram(*this));
    case Histogram::Saturation:
        return Histogram::sptr(new SaturationHistogram(*this));
    default:
        throw new IllegalArgumentException("Unsupported histogram type " + QString(type) + ".");
    }
}

}  // namespace frame
}  // namespace model