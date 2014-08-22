#include "RedHistogram.h"

#include "OpenGLException.h"

namespace model {
namespace frame {
namespace histogram {

using ::exception::OpenGLException;

RedHistogram::RedHistogram(const Surface &frame) {
    init(frame);
}

Histogram::HistogramType RedHistogram::getType() const {
    return HistogramType::Red;
}

QString RedHistogram::getGridFSFilePath() const {
    return ":/Shader/Histogram/redHistogramGrid.fs";
}

}  // namespace histogram
}  // namespace frame
}  // namespace model