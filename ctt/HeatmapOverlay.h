#if !defined(_HEATMAPOVERLAY_H)
#define _HEATMAPOVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "ColoringOverlay.h"
#include "Frame.h"
#include "Memento.h"
#include "PixelDiff.h"

namespace model {
namespace filter {
namespace overlay {

class HeatmapOverlay : public ColoringOverlay {
public:
	typedef QScopedPointer<HeatmapOverlay> uptr;
	typedef QSharedPointer<HeatmapOverlay> sptr;
	typedef QWeakPointer<HeatmapOverlay> wptr;

	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
private:
	PixelDiff* data;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_HEATMAPOVERLAY_H
