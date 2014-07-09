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
using ::exception::IllegalArgumentException;

Frame::Frame(QSharedPointer<QOpenGLContext> context, QImage image, FrameMetadata metadata)
        : Surface(context, image.size())
        , metadata(metadata) {
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