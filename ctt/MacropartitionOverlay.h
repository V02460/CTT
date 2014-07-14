#ifndef _MACROPARTITIONOVERLAY_H
#define _MACROPARTITIONOVERLAY_H

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
 * Provides a new version of the predecessors frame with the graphical representation of macropartitions mixed into it.
 */
class MacropartionOverlay : public Overlay {
public:
    typedef QScopedPointer<MacropartionOverlay> uptr;
    typedef QSharedPointer<MacropartionOverlay> sptr;
    typedef QWeakPointer<MacropartionOverlay> wptr;

    /**
     * Creates a new MacropartitionOverlay object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit MacropartionOverlay(Module::sptr predecessor);

    /**
     * MacropartionOverlay destructor.
     */
    virtual ~MacropartionOverlay();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE{ return true; }
    virtual QString getName() const;
    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MACROPARTITIONOVERLAY_H
