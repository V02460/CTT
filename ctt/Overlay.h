#ifndef _OVERLAY_H
#define _OVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"
#include "MixFilter.h"

namespace model {
namespace filter {
namespace overlay {

/**
 * An overlay modifies the frame of the predecessor by mixing it with any kind of graphical representable information.
 */
class Overlay : public ::model::filter::Filter {
public:
    typedef QScopedPointer<Overlay> uptr;
    typedef QSharedPointer<Overlay> sptr;
    typedef QWeakPointer<Overlay> wptr;

    static Saveable::SaveableType getSaveableType();

    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;

protected:
    /**
    * Constructs a Overlay which works on predecessor.
    *
    * @param predecessor The Module Overlay is receiving its Frames from.
    * @param overlay The image which is put on top
    * @param overlayAlpha The transparency of the overlay
    */
    explicit Overlay(Module::sptr predecessor, Module::sptr overlay, float overlayAlpha);

    /**
    * Overlay destructor.
    */
    virtual ~Overlay();

private:
    ::model::filter::MixFilter mixFilter;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_OVERLAY_H
