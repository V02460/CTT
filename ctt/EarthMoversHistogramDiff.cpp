#include "EarthMoversHistogramDiff.h"

namespace model {
namespace difference {

using ::model::frame::histogram::Histogram;
using ::model::frame::Frame;
using ::model::video::Video;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;

const QString EarthMoversHistogramDiff::VIDEO1 = "video1";
const QString EarthMoversHistogramDiff::VIDEO2 = "video2";
const QString EarthMoversHistogramDiff::TYPE = "type";

EarthMoversHistogramDiff::EarthMoversHistogramDiff(Histogram::HistogramType type,
                                                   Video::sptr video1,
                                                   Video::sptr video2) : FrameDiff(video1, video2),
												                         type(type) {}

EarthMoversHistogramDiff::~EarthMoversHistogramDiff() {
	isDummyFlag = true;
}

double EarthMoversHistogramDiff::getDiff(unsigned int frameNr) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
	if (frameNr > getFrameCount()) {
		throw new IllegalArgumentException("One or both videos have less then " + QString::number(frameNr)
			                               + " frames.");
	}
    Histogram::sptr a = Frame::getHistogram(video1->getFrame(frameNr), type);
    Histogram::sptr b = Frame::getHistogram(video2->getFrame(frameNr), type);
    float d[Histogram::kSize + 1];
	d[0] = 0;
	double sum = 0;
	for (int i = 0; i < Histogram::kSize; i++) {
		d[i + 1] = a->getValue(i) - b->getValue(i) + d[i];
		sum += std::abs(d[i + 1]);
    }

	return sum / (Histogram::kSize - 1);
}


Memento EarthMoversHistogramDiff::getMemento() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
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
	return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff());
}

Saveable::SaveableType EarthMoversHistogramDiff::getSaveableType() {
    return SaveableType::earthMoversHistogramDiff;
}

EarthMoversHistogramDiff::EarthMoversHistogramDiff() {
}

}  // namespace difference
}  // namespace model