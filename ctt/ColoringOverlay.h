#ifndef _COLORINGOVERLAY_H
#define _COLORINGOVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Overlay.h"
#include "Frame.h"
#include "Memento.h"
#include "GreyscaleFilter.h"

namespace model {
namespace filter {
namespace overlay {

/**
 * A ColoringOverlay modifies the frame of the predecessor in a similar way the Overlay does,
 * but it turns every frame to a greyscale frame before mixing it with the graphical representable information.
 */
class ColoringOverlay : public Overlay {
public:
    typedef QScopedPointer<ColoringOverlay> uptr;
    typedef QSharedPointer<ColoringOverlay> sptr;
    typedef QWeakPointer<ColoringOverlay> wptr;

    /**
     * ColoringOverlay destructor.
     */
    virtual ~ColoringOverlay();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE{ return true; }
	virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
	virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
	virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
    static Saveable::SaveableType getSaveableType() { return Saveable::coloringOverlay; }

protected:
    /**
     * Creates a new ColoringOverlay object with the given predecessor.
     * The overlay is rendered above the greyed out predecessor with with the given transparency.
     *
     * @param predecessor The previous module of this overlay.
     * @param overlay The module which content is rendered above the predecessor
     * @param overlayAlpha The transparency of the overlay
     */
    ColoringOverlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha);

    /**
     * Creates a dummy ColoringOverlay.
     */
    ColoringOverlay();

private:
    /**
     * Helper constructor to retrieve a handle to the created greyscale filter.
     */
    ColoringOverlay(Module::sptr greyscaleFilter,
                    Module::sptr predecessor,
                    Module::sptr overlay,
                    float overlayAlpha);

    Module::sptr greyscaleFilter;
};


}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_COLORINGOVERLAY_H
