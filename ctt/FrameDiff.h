


#if !defined(_FRAMEDIFF_H)
#define _FRAMEDIFF_H

#include "Saveable.h"
#include "Video.h"
#include "Memento.h"

/**
 * A FrameDiff compares corresponding frames from two specific videos and calculates one-dimensional distances between them.
 *
 */
class FrameDiff : public Saveable {
public:
    /**
     * Calculates and returns a one dimensional difference between the frames with the submitted number of the two videos this FrameDiff compares. A low value means the frames were similar, a high value indicates a huge difference.
     *
     * @param frameNr the frames with this number will be compared
     * @return double the calculated distance between the two frames
	 * @throws IllegalArgumentException if one or both of the videos don't have a frame with the submitted number
     */
    virtual double getDif(unsigned int frameNr);

	/**
	 * Returns the number of frames the shorter Video has, i.e. the number of frames the FrameDiff can calculate a difference to.
	 * @return unsigned int the number of frames the shorter Video has
	 */
	unsigned int getFrameCount();

    virtual Memento getMemento();

    virtual void restore(Memento memento);
protected:
    Video video1; /**< The first of the two Videos which this FrameDiff compares. */
    Video video2; /**< The second of the two Videos which this FrameDiff compares. */
};

#endif  //_FRAMEDIFF_H
