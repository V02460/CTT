#include "EarthMoversHistogramDiff.h"

namespace model {
namespace difference {

using ::model::frame::histogram::Histogram;
using ::model::video::Video;

EarthMoversHistogramDiff::EarthMoversHistogramDiff(Histogram::HistogramType type,
                                                   Video::sptr video1,
                                                   Video::sptr video2)
        : FrameDiff(video1, video2) {

}

EarthMoversHistogramDiff::~EarthMoversHistogramDiff() {

}

double EarthMoversHistogramDiff::getDiff(unsigned int frameNr) const {

}

}  // namespace difference
}  // namespace model