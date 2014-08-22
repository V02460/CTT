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

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }

protected:
    /**
     * Creates a new ColoringOverlay object with a given previous module.
     *
     * @param predecessor The previous module of this overlay.
     * @param overlay The image which is put on top
     * @param overlayAlpha The transparency of the overlay
     */
    explicit ColoringOverlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha);

private:
    ::model::filter::GreyscaleFilter::sptr greyscaleFilter;
};


}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_COLORINGOVERLAY_H
