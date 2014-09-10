#include "EarthMoversHistogramDiff.h"

namespace model {
namespace difference {

using ::model::frame::histogram::Histogram;
using ::model::frame::Frame;
using ::model::video::Video;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;

const QString EarthMoversHistogramDiff::kVideo1Str = "module1";
const QString EarthMoversHistogramDiff::kVideo2Str = "module2";
const QString EarthMoversHistogramDiff::kTypeStr = "type";

static QMap<Histogram::HistogramType, QByteArray> initDiffIDMap() {
    QMap<Histogram::HistogramType, QByteArray> diffIDs;
    diffIDs.insert(Histogram::Red, QT_TRANSLATE_NOOP("FrameDiff", "framediff_earthmoverhistogram_red"));
    diffIDs.insert(Histogram::Green, QT_TRANSLATE_NOOP("FrameDiff", "framediff_earthmoverhistogram_green"));
    diffIDs.insert(Histogram::Blue, QT_TRANSLATE_NOOP("FrameDiff", "framediff_earthmoverhistogram_blue"));
    diffIDs.insert(Histogram::Hue, QT_TRANSLATE_NOOP("FrameDiff", "framediff_earthmoverhistogram_hue"));
    diffIDs.insert(Histogram::Saturation, QT_TRANSLATE_NOOP("FrameDiff", "framediff_earthmoverhistogram_saturation"));
    diffIDs.insert(Histogram::Luminance, QT_TRANSLATE_NOOP("FrameDiff", "framediff_earthmoverhistogram_luminance"));
    return diffIDs;
}
const QMap<Histogram::HistogramType, QByteArray> EarthMoversHistogramDiff::kDiffIDs = initDiffIDMap();

EarthMoversHistogramDiff::EarthMoversHistogramDiff(Histogram::HistogramType type,
                                                   Video::sptr module1,
                                                   Video::sptr module2) : FrameDiff(module1, module2),
												                         type(type),
																		 diff() {}

EarthMoversHistogramDiff::~EarthMoversHistogramDiff() {}

QString EarthMoversHistogramDiff::getName() const {
    return QCoreApplication::translate("FrameDiff", kDiffIDs[type]);
}

double EarthMoversHistogramDiff::getDiff(unsigned int frameNr) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (frameNr > getFrameCount()) {
		throw IllegalArgumentException("One or both videos have less then " + QString::number(frameNr)
			                               + " frames.");
	}
	if (!diff.keys().contains(frameNr)) {
		calculateDiff(frameNr);
	}
	return diff.value(frameNr);
}

void EarthMoversHistogramDiff::calculateDiff(unsigned int frameNr) {
	Histogram::sptr a = Frame::getHistogram(module1->getFrame(frameNr), type);
	Histogram::sptr b = Frame::getHistogram(module2->getFrame(frameNr), type);
	float d[Histogram::kSize + 1];
	d[0] = 0;
	double sum = 0;
	for (int i = 0; i < Histogram::kSize; i++) {
		d[i + 1] = a->getValue(i) - b->getValue(i) + d[i];
		sum += std::abs(d[i + 1]);
	}
	diff.insert(frameNr, sum / (Histogram::kSize - 1));
}

Memento EarthMoversHistogramDiff::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	Memento memento;
	memento.setSharedPointer(kVideo1Str, module1);
	memento.setSharedPointer(kVideo2Str, module2);
	memento.setString(kTypeStr, Histogram::HISTOGRAM_TYPE_STRINGS[type]);
	return memento;
}

void EarthMoversHistogramDiff::restore(Memento memento) {
	module1 = memento.getSharedPointer(kVideo1Str).dynamicCast<Video>();
	module2 = memento.getSharedPointer(kVideo2Str).dynamicCast<Video>();
	type = Histogram::stringToType(memento.getString(kTypeStr));
	isDummyFlag = false;
}

Saveable::sptr EarthMoversHistogramDiff::getDummy() {
	return EarthMoversHistogramDiff::sptr(new EarthMoversHistogramDiff());
}

EarthMoversHistogramDiff::EarthMoversHistogramDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model