#include "GreenHistogram.h"

#include "OpenGLException.h"

namespace model {
namespace frame {
namespace histogram {

using ::exception::OpenGLException;

GreenHistogram::GreenHistogram(Surface::sptr frame) {
    init(frame);
}

Histogram::HistogramType GreenHistogram::getType() const {
    return HistogramType::Green;
}

QString GreenHistogram::getGridFSFilePath() const {
    return ":/Shader/Histogram/greenHistogramGrid.fs";
}

}  // namespace histogram
}  // namespace frame
}  // namespace model