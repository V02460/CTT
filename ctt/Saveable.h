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
	 * When updating this enum please also update the SAVEABLE_TYPE_STRINGS map by updating the initSTS() method.
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
        invertFilter,
		mixFilter,
		noiseFilter,
		overlay,
		coloringOverlay,
		heatmapOverlay,
        heatmapOverlay_heatmap,
		macroblockOverlay,
        macroblockOverlay_macroblocks,
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
		aBXTest
	};

	/**
	 * A list of string representations for saveable classes.
	 *
	 * This list must be similar in quantity and order to the SavableType enum. 
	 */
	static const QMap<SaveableType, QString> SAVEABLE_TYPE_STRINGS;

	/**
	 * Returns the type represented by the given string.
	 *
	 * @param string The string representation of the type to return.
	 * @return The type represented by the given string.
	 */
	static const SaveableType stringToSaveableType(QString string);

	/**
	 * Returns the type of the savable object.
	 *
	 * @return The type of the savable object.
	 */
	static SaveableType getSaveableType();

	virtual SaveableType saveableType() const = 0;

protected:
	bool isDummyFlag = false;

private:
	static const QMap<SaveableType, QString> initSTS();
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
18		|  |  |  |> MotionVektorOverlay
19		|  |  |> RescaleFilter
20		|  |  |> RGBChannelFilter
21		|  |  |> TimeshiftFilter
22		|  |> Video
23		|     |> FileVideo
24		|     |  |> YUVDataVideo
25		|     |> FilteredVideo
26		|> Player
27		|> SaveableList
28		|> UIntegerInterval
29		|> VideoScrubber

*/