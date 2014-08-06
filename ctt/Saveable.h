#ifndef _SAVEABLE_H
#define _SAVEABLE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Observer.h"

//#include "Memento.h"
namespace model {
namespace saveable {
    class Memento;
}}


namespace model {
namespace saveable {

/**
 * Objects, whose state can be externalized into a memento and restored from one.
 */
class Saveable {

public:
	typedef QScopedPointer<Saveable> uptr;
	typedef QSharedPointer<Saveable> sptr;
	typedef QWeakPointer<Saveable> wptr;

	/**
	 * The destructor of this class.
	 */
    virtual ~Saveable() = 0 {} // must have an implementation (linking errors, probably MOC)

    /**
     * Gets the internal state of the object as a Memento.
     *
     * @return Memento the internal state of the object
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual Memento getMemento() const = 0;

    /**
     * Sets the internal state of the object to the state saved in a submitted Memento.
     *
     * @param memento this state will be restored
	 * @throws IllegalArgumentException if the memento doesn't contain the data the object requires to restore itself
     */
	virtual void restore(Memento memento) = 0;

    /**
     * Creates and returns a dummy instance of the class with the sole purpose to have a state restored from a Memento.
     *
     * @return Saveable the dummy object
	 * @throws NotImplementedException if this method is called on a class which isn't meant to be instantiable
     */
    static Saveable::sptr getDummy();

	/**
	 * Checks whether the object is a dummy object.
	 *
	 * @return boolean true only if the object is a dummy
	 */
	bool isDummy() const;

	/**
	 * Labels for the different saveables.
	 *
	 * This enum must be similar in quantity and order to the SAVEABLE_TYPE_STRINGS list. 
	 */
	enum SaveableType {
		saveable,
		filterIntervalList,
		frameDiff,
		earthMoversHistogramDiff,
		pixelDiff,
		hSLPixelDiff,
		yUVPixelDiff,
		module,
		filter,
		blurFilter,
		coffeeFilter,
		greyscaleFilter,
		mixFilter,
		noiseFilter,
		overlay,
		coloringOverlay,
		heatmapOverlay,
		macroblockOverlay,
		makropartitionOverlay,
		motionVektorOverlay,
		rescaleFilter,
		rGBChannelFilter,
		timeshiftFilter,
		video,
		fileVideo,
		fFmpegDataVideo,
		yUVDataVideo,
		filteredVideo,
		player,
		saveableList,
		uIntegerInterval,
		videoScrubber,
		viewState
	};

	/** A string representation for the Saveable class. */
	static const QString SAVEABLE;
	/** A string representation for the FilterIntervalList class. */
	static const QString FILTER_INTERVAL_LIST;
	/** A string representation for the FrameDiff class. */
	static const QString FRAME_DIFF;
	/** A string representation for the EarthMoversHistogramDiff class. */
	static const QString EARTH_MOVERS_HISTOGRAM_DIFF;
	/** A string representation for the PixelDiff class. */
	static const QString PIXEL_DIFF;
	/** A string representation for the HSLPixelDiff class. */
	static const QString HSL_PIXEL_DIFF;
	/** A string representation for the YUVPixelDiff class. */
	static const QString YUV_PIXEL_DIFF;
	/** A string representation for the Module class. */
	static const QString MODULE;
	/** A string representation for the Filter class. */
	static const QString FILTER;
	/** A string representation for the BlurFilter class. */
	static const QString BLUR_FILTER;
	/** A string representation for the CoffeeFilter class. */
	static const QString COFFEE_FILTER;
	/** A string representation for the GreyscaleFilter class. */
	static const QString GREYSCALE_FILTER;
	/** A string representation for the MixFilter class. */
	static const QString MIX_FILTER;
	/** A string representation for the NoiseFilter class. */
	static const QString NOISE_FILTER;
	/** A string representation for the Overlay class. */
	static const QString OVERLAY;
	/** A string representation for the ColoringOverlay class. */
	static const QString COLORING_OVERLAY;
	/** A string representation for the HeatmapOverlay class. */
	static const QString HEATMAP_OVERLAY;
	/** A string representation for the MacroblockOverlay class. */
	static const QString MACROBLOCK_OVERLAY;
	/** A string representation for the MakropartitionOverlay class. */
	static const QString MAKROPARTITION_OVERLAY;
	/** A string representation for the MotionVektorOverlay class. */
	static const QString MOTION_VEKTOR_OVERLAY;
	/** A string representation for the RescaleFilter class. */
	static const QString RESCALE_FILTER;
	/** A string representation for the RGBChannelFilter class. */
	static const QString RGB_CHANNEL_FILTER;
	/** A string representation for the TimeshiftFilter class. */
	static const QString TIMESHIFT_FILTER;
	/** A string representation for the Video class. */
	static const QString VIDEO;
	/** A string representation for the FileVideo class. */
	static const QString FILE_VIDEO;
	/** A string representation for the FFmpegDataVideo class. */
	static const QString FFMPEG_DATA_VIDEO;
	/** A string representation for the YUVDataVideo class. */
	static const QString YUV_DATA_VIDEO;
	/** A string representation for the FilteredVideo class. */
	static const QString FILTERED_VIDEO;
	/** A string representation for the Player class. */
	static const QString PLAYER;
	/** A string representation for the SaveableList class. */
	static const QString SAVEABLE_LIST;
	/** A string representation for the UIntegerInterval class. */
	static const QString U_INTEGER_INTERVAL;
	/** A string representation for the VideoScrubber class. */
	static const QString VIDEO_SCRUBBER;
	/** A string representation for the ViewState class. */
	static const QString VIEW_STATE;

	/**
	 * A list of string representations for saveable classes.
	 *
	 * This list must be similar in quantity and order to the SavableType enum. 
	 */
	static const QList<QString> SAVEABLE_TYPE_STRINGS;

	/**
	 * Returns the type represented by the given string.
	 *
	 * @param string The string representation of the type to return.
	 * @return The type represented by the given string.
	 */
	static const SaveableType getType(QString string);

	/**
	 * Returns the type of the savable object.
	 *
	 * @return The type of the savable object.
	 */
	virtual SaveableType getType() const = 0;

protected:
	bool isDummyFlag = false;
};

}  // namespace savable
}  // namespace model

#endif  //_Saveable_H


/* tree of saveable classes:

 0		Saveable
 1		|> FilterIntervalList
 2		|> FrameDiff
 3		|  |> EarthMoversHistogramDiff
 4		|  |> PixelDiff
 5		|     |> HSLPixelDiff
 6		|     |> YUVPixelDiff
 7		|> Module
 8		|  |> Filter
 9		|  |  |> BlurFilter
10		|  |  |> CoffeeFilter
11		|  |  |> GreyscaleFilter
12		|  |  |> MixFilter
13		|  |  |> NoiseFilter
14		|  |  |> Overlay
15		|  |  |  |> ColoringOverlay
16		|  |  |  |  |> HeatmapOverlay
17		|  |  |  |  |> MacroblockOverlay
18		|  |  |  |> MakropartitionOverlay
19		|  |  |  |> MotionVektorOverlay
20		|  |  |> RescaleFilter
21		|  |  |> RGBChannelFilter
22		|  |  |> TimeshiftFilter
23		|  |> Video
24		|     |> FileVideo
25		|     |  |> FFmpegDataVideo
26		|     |  |> YUVDataVideo
27		|     |> FilteredVideo
28		|> Player
29		|> SaveableList
30		|> UIntegerInterval
31		|> VideoScrubber
32		|> ViewState

*/