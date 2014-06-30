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

	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};


}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_COLORINGOVERLAY_H
