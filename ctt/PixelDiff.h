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
 * A PixelDiff compares corresponding frames from two specific videos and calculates one- or two-dimensional distances
 * between them.
 */
class PixelDiff : public FrameDiff {
public:
	typedef QScopedPointer<PixelDiff> uptr;
	typedef QSharedPointer<PixelDiff> sptr;
	typedef QWeakPointer<PixelDiff> wptr;

	/**
	* Constructs the PixelDiff by taking two videos used to calculate their frame difference.
	*
	* @param video1 First Video used for comparisson
	* @param video2 Second Video comparisson
	*/
	PixelDiff(const video::Video &video1, const video::Video &video2);

	/**
	* PixelDiff Destructor
	*/
	virtual ~PixelDiff();

	/**
	* Calculates and returns a two-dimensional, pixel by pixel difference between the frames with the submitted number
	* of the two videos this PixelDiff compares. A low value means the frames were similar, a high value indicates a
	* huge difference.
	* For every pair of corresponding pixels, the distance is written to the corresponding texel in the surface.
	* 
	* @param frameNr the frames with this number will be compared
	* @return Surface the calculated distance between the two frames
	* @throws IllegalArgumentException if one or both of the videos don't have a frame with the submitted number
	*/
	virtual Surface getPixelDiff(unsigned int frameNr) const = 0;
};

}  // namespace difference
}  // namespace model

#endif  //_PIXELDIFF_H
