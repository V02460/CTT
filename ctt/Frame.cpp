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

    if (image.size().isEmpty()) {
        throw IllegalArgumentException("Tried to create a frame from an image of size "
                                           + QString::number(image.size().width()) + "*"
                                           + QString::number(image.size().height())
                                           + " but sizes of 0 are not allowed.");
    }
    if (metadata.getSize().isEmpty()) {
        throw IllegalArgumentException("Tried to create a frame with metadata describing a frame of size "
                                           + QString::number(metadata.getSize().width()) + "*"
                                           + QString::number(metadata.getSize().height())
                                           + " but sizes of 0 are not allowed.");
    }
    if (image.size() != metadata.getSize()) {
        throw IllegalArgumentException("Tried to create a frame from an image of size " 
                                           + QString::number(image.size().width()) + "*"
                                           + QString::number(image.size().height())
                                           + " but the submitted metadata specified a size of "
                                           + QString::number(metadata.getSize().width()) + "*"
                                           + QString::number(metadata.getSize().height()) + ".");
    }
    
    getTexture()->setData(image.mirrored(), QOpenGLTexture::DontGenerateMipMaps);
    getTexture()->setMinMagFilters(QOpenGLTexture::NearestMipMapNearest, QOpenGLTexture::NearestMipMapNearest);
}

Frame::Frame(QSharedPointer<QOpenGLContext> context, QImage image)
    : Surface(context, image.size())
    , metadata(FrameMetadata(image.size())) {

    if (image.size().isEmpty()) {
        throw IllegalArgumentException("Tried to create a frame from an image of size "
                                           + QString::number(image.size().width()) + "*"
                                           + QString::number(image.size().height())
                                           + " but sizes of 0 are not allowed.");
    }

    getTexture()->setData(image.mirrored(), QOpenGLTexture::DontGenerateMipMaps);
    getTexture()->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
}

Frame::Frame(QSharedPointer<QOpenGLContext> context, FrameMetadata metadata)
        : Surface(context, metadata.getSize())
        , metadata(metadata) {
    if (metadata.getSize().isEmpty()) {
        throw IllegalArgumentException("Tried to create a frame with metadata describing a frame of size "
                                           + QString::number(metadata.getSize().width()) + "*"
                                           + QString::number(metadata.getSize().height())
                                           + " but sizes of 0 are not allowed.");
    }
}

FrameMetadata Frame::getMetadata() const {
    return metadata;
}

Histogram::sptr Frame::getHistogram(Frame::sptr frame, Histogram::HistogramType type) {
    switch (type)
    {
    case Histogram::Red:
        return Histogram::sptr(new RedHistogram(frame));
    case Histogram::Green:
        return Histogram::sptr(new GreenHistogram(frame));
    case Histogram::Blue:
        return Histogram::sptr(new BlueHistogram(frame));
    case Histogram::Luminance:
        return Histogram::sptr(new LuminanceHistogram(frame));
    case Histogram::Hue:
        return Histogram::sptr(new HueHistogram(frame));
    case Histogram::Saturation:
        return Histogram::sptr(new SaturationHistogram(frame));
    default:
        throw IllegalArgumentException("Unsupported histogram type " + QString(type) + ".");
    }
}

Frame::Frame(Surface::sptr surface, FrameMetadata metadata) : Surface(*surface.data()), metadata(metadata) {
    if (metadata.getSize().isEmpty()) {
        throw IllegalArgumentException("Tried to create a frame with metadata describing a frame of size "
                                           + QString::number(metadata.getSize().width()) + "*"
                                           + QString::number(metadata.getSize().height())
                                           + " but sizes of 0 are not allowed.");
    }
    if (getSize() != metadata.getSize()) {
        throw IllegalArgumentException("Tried to create a frame from an image of size "
                                           + QString::number(getSize().width()) + "*"
                                           + QString::number(getSize().height())
                                           + " but the submitted metadata specified a size of "
                                           + QString::number(metadata.getSize().width()) + "*"
                                           + QString::number(metadata.getSize().height()) + ".");
    }
}

}  // namespace frame
}  // namespace model