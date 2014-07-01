#include "EarthMoversHistogramDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

EarthMoversHistogramDiff::EarthMoversHistogramDiff(const video::Video &video1, const video::Video &video2)
        : FrameDiff(video1, video2) {

}

EarthMoversHistogramDiff::~EarthMoversHistogramDiff() {

}

double EarthMoversHistogramDiff::getDiff(unsigned int frameNr) const {

}

}  // namespace difference
}  // namcespace model