#if !defined(_COLORINGOVERLAY_H)
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
	 *	A ColoringOverlay modifies the frame of the predecessor in a similar way the Overlay does,
	 *	but it turns every frame to a greyscale frame before mixig it with the graphical representable information.
	 */
class ColoringOverlay : public model::filter::overlay::Overlay {
public:
	typedef QScopedPointer<ColoringOverlay> uptr;
	typedef QSharedPointer<ColoringOverlay> sptr;
	typedef QWeakPointer<ColoringOverlay> wptr;

	ColoringOverlay(const Module &predecessor);
	virtual ~ColoringOverlay();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;

protected:
	const model::filter::GreyscaleFilter &getGreyscaleFilter() const;

private:
	model::filter::GreyscaleFilter::uptr greyscaleFilter;
};


}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_COLORINGOVERLAY_H
