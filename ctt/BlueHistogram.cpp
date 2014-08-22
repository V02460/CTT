#include "BlueHistogram.h"

namespace model {
namespace frame {
namespace histogram {

BlueHistogram::BlueHistogram(const Frame &frame) {
    init(frame);
}

Histogram::HistogramType BlueHistogram::getType() const {
    return HistogramType::Blue;
}

QString BlueHistogram::getGridFSFilePath() const {
    return ":/Shader/Histogram/blueHistogramGrid.fs";
}

}  // namespace histogram
}  // namespace frame
}  // namespace model