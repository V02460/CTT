#include "SaturationHistogram.h"

#include "OpenGLException.h"

namespace model {
namespace frame {
namespace histogram {

using ::exception::OpenGLException;

SaturationHistogram::SaturationHistogram(const Frame &frame) {
    init(frame);
}

Histogram::HistogramType SaturationHistogram::getType() const {
    return HistogramType::Saturation;
}

QString SaturationHistogram::getGridFSFilePath() const {
    return ":/Shader/Histogram/saturationHistogramGrid.fs";
}

}  // namespace histogram
}  // namespace frame
}  // namespace model