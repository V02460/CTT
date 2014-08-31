#ifndef _HEATMAPOVERLAY_H
#define _HEATMAPOVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "ColoringOverlay.h"
#include "Frame.h"
#include "Memento.h"
#include "PixelDiff.h"

namespace model {
namespace filter {
namespace overlay {

/**
 * Provides a new version of the predecessors frame where any PixelDiff was mixed graphically into it.
 */
class HeatmapOverlay : public ColoringOverlay {
    Q_OBJECT

public:
    typedef QScopedPointer<HeatmapOverlay> uptr;
    typedef QSharedPointer<HeatmapOverlay> sptr;
    typedef QWeakPointer<HeatmapOverlay> wptr;

    static const QByteArray kFilterID;

    /**
     * Creates a new HeatmapOverlay object with a given previous module and a PixelDiff function which should be
     * displayed.
     *
     * @param predecessor The previous module of this overlay.
     * @param difference The difference that should be displayed.
     */
    HeatmapOverlay(Module::sptr predecessor, ::model::difference::PixelDiff::sptr difference);
    
    /**
     * HeatmapOverlay destructor.
     */
    virtual ~HeatmapOverlay();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("Filter", kFilterID); }
    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
    virtual QList<const ::model::Module*> getUsesList() const Q_DECL_OVERRIDE;
	virtual ::model::saveable::Memento getMemento() const;
	virtual void restore(::model::saveable::Memento memento);
	static Saveable::sptr getDummy();
    static Saveable::SaveableType getSaveableType() { return Saveable::heatmapOverlay; }

private:
    ::model::difference::PixelDiff::uptr data;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_HEATMAPOVERLAY_H
