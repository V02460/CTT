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
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_MACROBLOCKOVERLAY_H
