#if !defined(_OVERLAY_H)
#define _OVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {
namespace overlay {

/**
 *	An overlay modifies the frame of the predecessor by mixing it with any kind of graphical representable information.
 */
class Overlay : public Filter {
public:
	typedef QScopedPointer<Overlay> uptr;
	typedef QSharedPointer<Overlay> sptr;
	typedef QWeakPointer<Overlay> wptr;

	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_OVERLAY_H
