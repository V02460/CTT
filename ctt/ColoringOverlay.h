#if !defined(_COLORINGOVERLAY_H)
#define _COLORINGOVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Overlay.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {
namespace overlay {

class ColoringOverlay : public Overlay {
public:
	typedef QScopedPointer<ColoringOverlay> uptr;
	typedef QSharedPointer<ColoringOverlay> sptr;
	typedef QWeakPointer<ColoringOverlay> wptr;

	ColoringOverlay(const Module &predecessor);
	virtual ~ColoringOverlay();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};


}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_COLORINGOVERLAY_H
