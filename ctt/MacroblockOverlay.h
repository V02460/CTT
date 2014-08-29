#ifndef _MACROBLOCKOVERLAY_H
#define _MACROBLOCKOVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "ColoringOverlay.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {
namespace overlay {

/**
 * Provides a new version of the predecessors frame with the graphical representation of macroblock types mixed into it.
 */
class MacroblockOverlay : public ColoringOverlay {
public:
    typedef QScopedPointer<MacroblockOverlay> uptr;
    typedef QSharedPointer<MacroblockOverlay> sptr;
    typedef QWeakPointer<MacroblockOverlay> wptr;

    static const QByteArray kFilterID;

    /**
     * Creates a new MacroblockOverlay object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit MacroblockOverlay(Module::sptr predecessor);

    /**
     * MacroblockOverlay destructor.
     */
    virtual ~MacroblockOverlay();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE{ return true; }
    virtual QString getName() const Q_DECL_OVERRIDE { return tr(kFilterID); }
	virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
    virtual QList<const ::model::Module*> getUsesList() const Q_DECL_OVERRIDE;
    virtual bool uses(const ::model::Module &module) const Q_DECL_OVERRIDE;
    static Saveable::SaveableType getSaveableType();
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MACROBLOCKOVERLAY_H
