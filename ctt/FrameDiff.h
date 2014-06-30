#if !defined(_FRAMEDIFF_H)
#define _FRAMEDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Saveable.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

/**
 * A FrameDiff compares corresponding frames from two specific videos and calculates one-dimensional distances between them.
 *
 */
class FrameDiff : public project::Saveable {
public:
	typedef QScopedPointer<FrameDiff> uptr;
	typedef QSharedPointer<FrameDiff> sptr;
	typedef QWeakPointer<FrameDiff> wptr;

	/**
	 * Constructs the FrameDiff by taking two videos used to calculate their frame difference.
	 *
	 * @param video1 First video used for comparisson
	 * @param video2 Second video comparisson
	 */
	FrameDiff(const video::Video &video1, const video::Video &video2);

	/**
	 * FrameDiff Destructor
	 */
	virtual ~FrameDiff();

    /**
     * Calculates and returns a one dimensional difference between the frames with the submitted number of the two videos this FrameDiff compares. A low value means the frames were similar, a high value indicates a huge difference.
     *
     * @param frameNr the frames with this number will be compared
     * @return double the calculated distance between the two frames
	 * @throws IllegalArgumentException if one or both of the videos don't have a frame with the submitted number
     */
    virtual double getDiff(unsigned int frameNr) const = 0;

	/**
	 * Returns the number of frames the shorter Video has, i.e. the number of frames the FrameDiff can calculate a difference to.
	 *
	 * @return unsigned int the number of frames the shorter Video has
	 */
	unsigned int getFrameCount() const;
protected:
    video::Video video1; /**< The first of the two Videos which this FrameDiff compares. */
    video::Video video2; /**< The second of the two Videos which this FrameDiff compares. */

private:
	FrameDiff();
};

}  // namespace difference
}  // namespace model

#endif  //_FRAMEDIFF_H
