#include "EarthMoversHistogramDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::frame::histogram::Histogram;
using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

EarthMoversHistogramDiff::EarthMoversHistogramDiff(Histogram::HistogramType type,
                                                   Video::sptr video1,
                                                   Video::sptr video2)
        : FrameDiff(video1, video2) {
    throw new NotImplementedException();
}

EarthMoversHistogramDiff::~EarthMoversHistogramDiff() {
    throw new NotImplementedException();
}

double EarthMoversHistogramDiff::getDiff(unsigned int frameNr) const {
    throw new NotImplementedException();
}

Saveable::SaveableType EarthMoversHistogramDiff::getType() const {
	return Saveable::SaveableType::earthMoversHistogramDiff;
}

}  // namespace difference
}  // namespace model