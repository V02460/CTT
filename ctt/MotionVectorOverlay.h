#if !defined(_MOTIONVECTOROVERLAY_H)
#define _MOTIONVECTOROVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Overlay.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {
namespace overlay {

/**
 *	Provides a new version of the predecessors frame with the graphical representation of motion vectors mixed into it.
 */
class MotionVectorOverlay : public Overlay {
public:
	typedef QScopedPointer<MotionVectorOverlay> uptr;
	typedef QSharedPointer<MotionVectorOverlay> sptr;
	typedef QWeakPointer<MotionVectorOverlay> wptr;

	/**
	*	Creates a new MotionVectorOverlay object with a given previous module.
	*
	*	@param predecessor The previous module of this filter.
	*/
	MotionVectorOverlay(const Module &predecessor);
	virtual ~MotionVectorOverlay();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MOTIONVECTOROVERLAY_H
