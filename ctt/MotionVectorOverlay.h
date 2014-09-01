#ifndef _MOTIONVECTOROVERLAY_H
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
 * Provides a new version of the predecessors frame with the graphical representation of motion vectors mixed into it.
 */
class MotionVectorOverlay : public Overlay {
    Q_OBJECT

public:
    typedef QScopedPointer<MotionVectorOverlay> uptr;
    typedef QSharedPointer<MotionVectorOverlay> sptr;
    typedef QWeakPointer<MotionVectorOverlay> wptr;

    static const QByteArray kFilterID;

    /**
    * Creates a new MotionVectorOverlay object with a given previous module.
    *
    * @param predecessor The previous module of this filter.
    */
    explicit MotionVectorOverlay(Module::sptr predecessor);

    /**
     * MotionVectorOverlay destructor.
     */
    virtual ~MotionVectorOverlay();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const Q_DECL_OVERRIDE { return kFilterID; }
	virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
	virtual QList<const ::model::Module*> getUsesList() const Q_DECL_OVERRIDE;
	virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
	static Saveable::SaveableType getSaveableType() { return Saveable::motionVektorOverlay; }
	virtual SaveableType saveableType();
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MOTIONVECTOROVERLAY_H
