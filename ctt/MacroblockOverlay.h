#if !defined(_MACROBLOCKOVERLAY_H)
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

class MacroblockOverlay : public ColoringOverlay {
public:
	typedef QScopedPointer<MacroblockOverlay> uptr;
	typedef QSharedPointer<MacroblockOverlay> sptr;
	typedef QWeakPointer<MacroblockOverlay> wptr;

	MacroblockOverlay(const Module &predecessor);
	virtual ~MacroblockOverlay();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MACROBLOCKOVERLAY_H
