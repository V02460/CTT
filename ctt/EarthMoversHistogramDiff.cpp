#include "EarthMoversHistogramDiff.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::frame::histogram::Histogram;
using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::frame::Histogram;
using ::model::saveable::Memento;

EarthMoversHistogramDiff::EarthMoversHistogramDiff(Histogram::HistogramType type,
                                                   Video::sptr video1,
                                                   Video::sptr video2)
        : FrameDiff(video1, video2), type(type) {}

EarthMoversHistogramDiff::~EarthMoversHistogramDiff() {}

const QString EarthMoversHistogramDiff::VIDEO1 = "video1";
const QString EarthMoversHistogramDiff::VIDEO2 = "video2";
const QString EarthMoversHistogramDiff::TYPE = "type";

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
		// TODO replace getValue
		//d[i + 1] = a->getValue(i) - b->getValue(i) + d[i];
		sum += std::abs(d[i + 1]);
	}
	// TODO scale
	return sum;
}

EarthMoversHistogramDiff::EarthMoversHistogramDiff() {}

Memento EarthMoversHistogramDiff::getMemento() const {
	Memento memento;
	memento.setSharedPointer(VIDEO1, video1);
	memento.setSharedPointer(VIDEO2, video2);
	memento.setString(TYPE, Histogram::HISTOGRAM_TYPE_STRINGS[type]);
	return memento;
}

void EarthMoversHistogramDiff::restore(Memento memento) {
	video1 = memento.getSharedPointer(VIDEO1).dynamicCast<Video>();
	video2 = memento.getSharedPointer(VIDEO2).dynamicCast<Video>();
	type = Histogram::stringToType(memento.getString(TYPE));
	isDummyFlag = false;
}

Saveable::sptr EarthMoversHistogramDiff::getDummy() {
	EarthMoversHistogramDiff *dummy = new EarthMoversHistogramDiff();
	dummy->isDummyFlag = true;
	EarthMoversHistogramDiff::sptr dummyPointer = QSharedPointer<EarthMoversHistogramDiff>(dummy);
	return dummyPointer;
}

Saveable::SaveableType EarthMoversHistogramDiff::getType() const {
	return Saveable::SaveableType::earthMoversHistogramDiff;
}

}  // namespace difference
}  // namespace model