#include "Saveable.h"

#include "NotImplementedException.h"
#include "IllegalArgumentException.h"

namespace model {
namespace saveable {

using ::exception::NotImplementedException;
using ::exception::IllegalArgumentException;

const QString Saveable::SAVEABLE = "Saveable";
const QString Saveable::FILTER_INTERVAL_LIST = "FilterIntervalList";
const QString Saveable::FRAME_DIFF = "FrameDiff";
const QString Saveable::EARTH_MOVERS_HISTOGRAM_DIFF = "EarthMoversHistogramDiff";
const QString Saveable::PIXEL_DIFF = "PixelDiff";
const QString Saveable::HSL_PIXEL_DIFF = "HSLPixelDiff";
const QString Saveable::YUV_PIXEL_DIFF = "YUVPixelDiff";
const QString Saveable::MODULE = "Module";
const QString Saveable::FILTER = "Filter";
const QString Saveable::BLUR_FILTER = "BlurFilter";
const QString Saveable::COFFEE_FILTER = "CoffeeFilter";
const QString Saveable::GREYSCALE_FILTER = "GreyscaleFilter";
const QString Saveable::MIX_FILTER = "MixFilter";
const QString Saveable::NOISE_FILTER = "NoiseFilter";
const QString Saveable::OVERLAY = "Overlay";
const QString Saveable::COLORING_OVERLAY = "ColoringOverlay";
const QString Saveable::HEATMAP_OVERLAY = "HeatmapOverlay";
const QString Saveable::MACROBLOCK_OVERLAY = "MacroblockOverlay";
const QString Saveable::MAKROPARTITION_OVERLAY = "MakropartitionOverlay";
const QString Saveable::MOTION_VEKTOR_OVERLAY = "MotionVektorOverlay";
const QString Saveable::RESCALE_FILTER = "RescaleFilter";
const QString Saveable::RGB_CHANNEL_FILTER = "RGBChannelFilter";
const QString Saveable::TIMESHIFT_FILTER = "TimeshiftFilter";
const QString Saveable::VIDEO = "Video";
const QString Saveable::FILE_VIDEO = "FileVideo";
const QString Saveable::FFMPEG_DATA_VIDEO = "FFmpegDataVideo";
const QString Saveable::YUV_DATA_VIDEO = "YUVDataVideo";
const QString Saveable::FILTERED_VIDEO = "FilteredVideo";
const QString Saveable::PLAYER = "Player";
const QString Saveable::SAVEABLE_LIST = "SaveableList";
const QString Saveable::U_INTEGER_INTERVAL = "UIntegerInterval";
const QString Saveable::VIDEO_SCRUBBER = "VideoScrubber";
const QString Saveable::VIEW_STATE = "ViewState";

const QList<QString> Saveable::SAVEABLE_TYPE_STRINGS = QList<QString>()
	<< SAVEABLE
	<< FILTER_INTERVAL_LIST
	<< FRAME_DIFF
	<< EARTH_MOVERS_HISTOGRAM_DIFF
	<< PIXEL_DIFF
	<< HSL_PIXEL_DIFF
	<< YUV_PIXEL_DIFF
	<< MODULE
	<< FILTER
	<< BLUR_FILTER
	<< COFFEE_FILTER
	<< GREYSCALE_FILTER
	<< MIX_FILTER
	<< NOISE_FILTER
	<< OVERLAY
	<< COLORING_OVERLAY
	<< HEATMAP_OVERLAY
	<< MACROBLOCK_OVERLAY
	<< MAKROPARTITION_OVERLAY
	<< MOTION_VEKTOR_OVERLAY
	<< RESCALE_FILTER
	<< RGB_CHANNEL_FILTER
	<< TIMESHIFT_FILTER
	<< VIDEO
	<< FILE_VIDEO
	<< FFMPEG_DATA_VIDEO
	<< YUV_DATA_VIDEO
	<< FILTERED_VIDEO
	<< PLAYER
	<< SAVEABLE_LIST
	<< U_INTEGER_INTERVAL
	<< VIDEO_SCRUBBER
	<< VIEW_STATE;

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
	for (int i = 0; i < SAVEABLE_TYPE_STRINGS.length(); i++) {
		if (string == SAVEABLE_TYPE_STRINGS[i]) {
			return static_cast<SaveableType>(i);
		}
	}
	throw IllegalArgumentException(string + " is not a saveable class type.");
}

}  // namespace savable
}  // namespace model