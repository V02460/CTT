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

class MotionVectorOverlay : public Overlay {
public:
	typedef QScopedPointer<MotionVectorOverlay> uptr;
	typedef QSharedPointer<MotionVectorOverlay> sptr;
	typedef QWeakPointer<MotionVectorOverlay> wptr;

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
