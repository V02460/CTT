#if !defined(_PIXELDIFF_H)
#define _PIXELDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "FrameDiff.h"
#include "Video.h"
#include "Memento.h"
#include "Frame.h"

namespace model {
namespace difference {

/**
 * A PixelDiff compares corresponding frames from two specific videos and calculates one- or two-dimensional distances between them.
 */
class PixelDiff : public FrameDiff {
public:
	/**
	* Calculates and returns a two-dimensional, pixel by pixel difference between the frames with the submitted number of the two videos this PixelDiff compares. A low value means the frames were similar, a high value indicates a huge difference.
	* For every pair of corresponding pixels, the distance is written to the corresponding texel in the surface.
	* 
	* @param frameNr the frames with this number will be compared
	* @return Surface the calculated distance between the two frames
	* @throws IllegalArgumentException if one or both of the videos don't have a frame with the submitted number
	*/
	virtual Surface getPixelDif(unsigned int frameNr);

	virtual double getDif(int frameNr);
	virtual void FrameDif(Video video1, Video video2);
	virtual Memento getMemento();
	virtual void restore(Memento memento);
	virtual Saveable* getDummy();
};

}  // namespace difference
}  // namespace model

#endif  //_PIXELDIFF_H
