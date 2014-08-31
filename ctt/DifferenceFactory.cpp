#include "DifferenceFactory.h"

#include "EarthMoversHistogramDiff.h"
#include "YUVPixelDiff.h"
#include "HSLPixelDiff.h"

#include "IllegalArgumentException.h"

namespace model {
namespace difference {

using ::model::difference::FrameDiff;
using ::model::video::Video;
using ::exception::IllegalArgumentException;
using ::model::frame::histogram::Histogram;

QList<QString> DifferenceFactory::getAllFrameDiffIDs() {
    return QList<QString>()
        << "framediff_earthmoverhistogram_red"
        << "framediff_earthmoverhistogram_green"
        << "framediff_earthmoverhistogram_blue"
        << "framediff_earthmoverhistogram_hue"
        << "framediff_earthmoverhistogram_saturation"
        << "framediff_earthmoverhistogram_luminance";
}

QList<QString> DifferenceFactory::getAllPixelDiffIDs() {
    return QList<QString>()
        << "pixeldiff_hsl"
        << "pixeldiff_yuv";
}

FrameDiff::sptr DifferenceFactory::createFrameDiff(QString id, Video::sptr video1, Video::sptr video2) {
    // TODO: change check to use shared group
    if (video1->getContext() != video2->getContext()) {
        throw IllegalArgumentException("OpenGL contexts of the two videos don't match.");
}

    if (id == "framediff_earthmover_red") {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Red, video1, video2));
    }
    if (id == "framediff_earthmover_green") {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Green, video1, video2));
    }
    if (id == "framediff_earthmover_blue") {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Blue, video1, video2));
    }
    if (id == "framediff_earthmover_hue") {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Hue, video1, video2));
    }
    if (id == "framediff_earthmover_saturation") {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Saturation, video1, video2));
    }
    if (id == "framediff_earthmover_luminance") {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Luminance, video1, video2));
    }

    throw IllegalArgumentException("Id does not match a FrameDiff.");
}

PixelDiff::sptr DifferenceFactory::createPixelDiff(QString id, Video::sptr video1, Video::sptr video2) {
    // TODO: change check to use shared group
    if (video1->getContext() != video2->getContext()) {
        throw IllegalArgumentException("OpenGL contexts of the two videos don't match.");
    }

    if (id == "pixeldiff_hsl") {
        return HSLPixelDiff::sptr(new HSLPixelDiff(video1, video2));
    }
    if (id == "pixeldiff_yuv") {
        return YUVPixelDiff::sptr(new YUVPixelDiff(video1, video2));
    }
    
    throw IllegalArgumentException("Id does not match a PixelDiff.");
}

}  // namespace difference
}  // namespace model