#if !defined(_MACROPARTITIONOVERLAY_H)
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

class MacropartionOverlay : public Overlay {
public:
	typedef QScopedPointer<MacropartionOverlay> uptr;
	typedef QSharedPointer<MacropartionOverlay> sptr;
	typedef QWeakPointer<MacropartionOverlay> wptr;

	MacropartionOverlay(const Module &predecessor);
	virtual ~MacropartionOverlay();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MACROPARTITIONOVERLAY_H
