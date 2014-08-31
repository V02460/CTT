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
    virtual QString getName() const;
    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;

	virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
	virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
	virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
	static ::model::saveable::Saveable::SaveableType getSaveableType() { return Saveable::coloringOverlay; }

protected:
    const ::model::filter::GreyscaleFilter &getGreyscaleFilter() const;

private:
    ::model::filter::GreyscaleFilter::uptr greyscaleFilter;
};


}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_COLORINGOVERLAY_H
