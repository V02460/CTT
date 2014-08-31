#include "LuminanceHistogram.h"

#include "OpenGLException.h"

namespace model {
namespace frame {
namespace histogram {

using ::exception::OpenGLException;

LuminanceHistogram::LuminanceHistogram(Surface::sptr frame) {
    init(frame);
}

Histogram::HistogramType LuminanceHistogram::getType() const {
    return HistogramType::Luminance;
}

QString LuminanceHistogram::getGridFSFilePath() const {
    return ":/Shader/Histogram/luminanceHistogramGrid.fs";
}

}  // namespace histogram
}  // namespace frame
}  // namespace model