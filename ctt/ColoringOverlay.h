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
class ColoringOverlay : public ::model::filter::overlay::Overlay {
public:
    typedef QScopedPointer<ColoringOverlay> uptr;
    typedef QSharedPointer<ColoringOverlay> sptr;
    typedef QWeakPointer<ColoringOverlay> wptr;

    /**
     * Creates a new ColoringOverlay object with a given previous module.
     *
     * @param predecessor The previous module of this overlay.
     */
    explicit ColoringOverlay(Module::sptr predecessor);

    /**
     * ColoringOverlay destructor.
     */
    virtual ~ColoringOverlay();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE{ return true; }
    QString getName() const;
    model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;


protected:
    const ::model::filter::GreyscaleFilter &getGreyscaleFilter() const;

private:
    ::model::filter::GreyscaleFilter::uptr greyscaleFilter;
};


}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_COLORINGOVERLAY_H
