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
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MACROPARTITIONOVERLAY_H
