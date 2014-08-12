#include "EarthMoversHistogramDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::frame::histogram::Histogram;
using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::frame::Histogram;

EarthMoversHistogramDiff::EarthMoversHistogramDiff(Histogram::HistogramType type,
                                                   Video::sptr video1,
                                                   Video::sptr video2)
        : FrameDiff(video1, video2), type(type) {}

EarthMoversHistogramDiff::~EarthMoversHistogramDiff() {}

double EarthMoversHistogramDiff::getDiff(unsigned int frameNr) const {
	if (frameNr > getFrameCount()) {
		throw new IllegalArgumentException("One or both videos have less then " + QString::number(frameNr)
			                               + " frames.");
	}
	Histogram::sptr a = video1->getFrame(frameNr)->getHistogram(type);
	Histogram::sptr b = video2->getFrame(frameNr)->getHistogram(type);

	float d[Histogram::SIZE + 1];
	d[0] = 0;
	int sum = 0;
	for (int i = 0; i < Histogram::SIZE; i++) {
		d[i + 1] = a->getValue(i) - b->getValue(i) + d[i];
		sum += std::abs(d[i + 1]);
	}
	// TODO scale
	return sum;
}

Saveable::SaveableType EarthMoversHistogramDiff::getType() const {
	return Saveable::SaveableType::earthMoversHistogramDiff;
}

}  // namespace difference
}  // namespace model