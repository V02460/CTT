#include "BlueHistogram.h"

namespace model {
namespace frame {
namespace histogram {

BlueHistogram::BlueHistogram(Frame frame) {

}

HistogramType BlueHistogram::getType() const {
    return HistogramType::Blue;
}

}  // namespace histogram
}  // namespace frame
}  // namespace model