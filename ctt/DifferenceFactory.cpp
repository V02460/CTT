#include "DifferenceFactory.h"

#include "EarthMoversHistogramDiff.h"
#include "YUVPixelDiff.h"
#include "HSLPixelDiff.h"

#include "IllegalArgumentException.h"

namespace model {
namespace difference {

using ::model::difference::FrameDiff;
using ::model::difference::EarthMoversHistogramDiff;
using ::model::video::Video;
using ::exception::IllegalArgumentException;
using ::model::frame::histogram::Histogram;

QList<QString> DifferenceFactory::getAllFrameDiffIDs() {
    return QList<QString>()
        << EarthMoversHistogramDiff::kDiffIDs[Histogram::Red]
        << EarthMoversHistogramDiff::kDiffIDs[Histogram::Green]
        << EarthMoversHistogramDiff::kDiffIDs[Histogram::Blue]
        << EarthMoversHistogramDiff::kDiffIDs[Histogram::Hue]
        << EarthMoversHistogramDiff::kDiffIDs[Histogram::Saturation]
        << EarthMoversHistogramDiff::kDiffIDs[Histogram::Luminance]
        << HSLPixelDiff::kDiffID
        << YUVPixelDiff::kDiffID;
}

QList<QString> DifferenceFactory::getAllPixelDiffIDs() {
    return QList<QString>()
        << HSLPixelDiff::kDiffID
        << YUVPixelDiff::kDiffID;
}

FrameDiff::sptr DifferenceFactory::createFrameDiff(QString id, Video::sptr video1, Video::sptr video2) {
    // TODO: change check to use shared group
    if (video1->getContext() != video2->getContext()) {
        throw IllegalArgumentException("OpenGL contexts of the two videos don't match.");
    }

    if (id == EarthMoversHistogramDiff::kDiffIDs[Histogram::Red]) {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Red, video1, video2));
    }
    if (id == EarthMoversHistogramDiff::kDiffIDs[Histogram::Green]) {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Green, video1, video2));
    }
    if (id == EarthMoversHistogramDiff::kDiffIDs[Histogram::Blue]) {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Blue, video1, video2));
    }
    if (id == EarthMoversHistogramDiff::kDiffIDs[Histogram::Hue]) {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Hue, video1, video2));
    }
    if (id == EarthMoversHistogramDiff::kDiffIDs[Histogram::Saturation]) {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Saturation, video1, video2));
    }
    if (id == EarthMoversHistogramDiff::kDiffIDs[Histogram::Luminance]) {
        return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff(Histogram::Luminance, video1, video2));
    }
    if (id == HSLPixelDiff::kDiffID) {
        return HSLPixelDiff::sptr(new HSLPixelDiff(video1, video2));
    }
    if (id == YUVPixelDiff::kDiffID) {
        return YUVPixelDiff::sptr(new YUVPixelDiff(video1, video2));
    }

    throw IllegalArgumentException("Id does not match a FrameDiff.");
}

PixelDiff::sptr DifferenceFactory::createPixelDiff(QString id, Video::sptr video1, Video::sptr video2) {
    // TODO: change check to use shared group
    if (video1->getContext() != video2->getContext()) {
        throw IllegalArgumentException("OpenGL contexts of the two videos don't match.");
    }

    if (id == HSLPixelDiff::kDiffID) {
        return HSLPixelDiff::sptr(new HSLPixelDiff(video1, video2));
    }
    if (id == YUVPixelDiff::kDiffID) {
        return YUVPixelDiff::sptr(new YUVPixelDiff(video1, video2));
    }
    
    throw IllegalArgumentException("Id does not match a PixelDiff.");
}

}  // namespace difference
}  // namespace model