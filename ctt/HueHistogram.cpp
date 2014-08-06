#include "HueHistogram.h"

#include "OpenGLException.h"

namespace model {
namespace frame {
namespace histogram {

using ::exception::OpenGLException;

HueHistogram::HueHistogram(const Surface &frame) {
    init(frame);
}

Histogram::HistogramType HueHistogram::getType() const {
    return HistogramType::Hue;
}

QString HueHistogram::getGridFSFilePath() const {
    return ":/Shader/Histogram/hueHistogramGrid.fs";
}

}  // namespace histogram
}  // namespace frame
}  // namespace model