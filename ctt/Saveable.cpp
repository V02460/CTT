#include "Saveable.h"

#include "Memento.h"
#include "NotImplementedException.h"
#include "IllegalArgumentException.h"

namespace model {
namespace saveable {

using ::model::saveable::Memento;
using ::exception::NotImplementedException;
using ::exception::IllegalArgumentException;

const QMap<Saveable::SaveableType, QString> Saveable::initSTS() {
	QMap<Saveable::SaveableType, QString> map;
	map.insert(Saveable::saveable, "Saveable");
	map.insert(Saveable::filterIntervalList, "FilterIntervalList");
	map.insert(Saveable::frameDiff, "FrameDiff");
	map.insert(Saveable::earthMoversHistogramDiff, "EarthMoversHistogramDiff");
	map.insert(Saveable::pixelDiff, "PixelDiff");
	map.insert(Saveable::hSLPixelDiff, "HSLPixelDiff");
	map.insert(Saveable::yUVPixelDiff, "YUVPixelDiff");
	map.insert(Saveable::module, "Module");
	map.insert(Saveable::filter, "Filter");
	map.insert(Saveable::blurFilter, "BlurFilter");
	map.insert(Saveable::coffeeFilter, "CoffeeFilter");
	map.insert(Saveable::greyscaleFilter, "GreyscaleFilter");
	map.insert(Saveable::invertFilter, "InvertFilter");
	map.insert(Saveable::mixFilter, "MixFilter");
	map.insert(Saveable::noiseFilter, "NoiseFilter");
	map.insert(Saveable::overlay, "Overlay");
	map.insert(Saveable::coloringOverlay, "ColoringOverlay");
	map.insert(Saveable::heatmapOverlay, "HeatmapOverlay");
	map.insert(Saveable::heatmapOverlay_heatmap, "HeatmapOverlay_heatmap");
	map.insert(Saveable::macroblockOverlay, "MacroblockOverlay");
	map.insert(Saveable::macroblockOverlay_macroblocks, "MacroblockOverlay_macroblocks");
	map.insert(Saveable::makropartitionOverlay, "MakropartitionOverlay");
	map.insert(Saveable::motionVektorOverlay, "MotionVektorOverlay");
	map.insert(Saveable::rescaleFilter, "RescaleFilter");
	map.insert(Saveable::rGBChannelFilter, "RGBChannelFilter");
	map.insert(Saveable::timeshiftFilter, "TimeshiftFilter");
	map.insert(Saveable::video, "Video");
	map.insert(Saveable::fileVideo, "FileVideo");
	map.insert(Saveable::fFmpegDataVideo, "FFmpegDataVideo");
	map.insert(Saveable::yUVDataVideo, "YUVDataVideo");
	map.insert(Saveable::filteredVideo, "FilteredVideo");
	map.insert(Saveable::player, "Player");
	map.insert(Saveable::saveableList, "SaveableList");
	map.insert(Saveable::uIntegerInterval, "UIntegerInterval");
	map.insert(Saveable::videoScrubber, "VideoScrubber");
	return map;
}

const QMap<Saveable::SaveableType, QString> Saveable::SAVEABLE_TYPE_STRINGS = initSTS();

Memento Saveable::getMemento() const {
    return Memento();
}

void Saveable::restore(Memento memento) {
    isDummyFlag = false;
}

bool Saveable::isDummy() const {
	return isDummyFlag;
}

Saveable::sptr Saveable::getDummy() {
    throw NotImplementedException();
}

Saveable::SaveableType Saveable::getSaveableType() {
    return SaveableType::saveable;
}

const Saveable::SaveableType Saveable::stringToSaveableType(QString string) {
	for each (SaveableType type in SAVEABLE_TYPE_STRINGS.keys()) {
		if (SAVEABLE_TYPE_STRINGS.value(type) == string) {
			return type;
		}
	}
	throw IllegalArgumentException(string + " is not a saveable class type.");
}

}  // namespace savable
}  // namespace model