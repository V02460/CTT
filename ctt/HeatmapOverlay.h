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

/**
 *	Provides a new version of the predecessors frame where any PixelDiff was mixed graphically into it.
 */
class HeatmapOverlay : public ColoringOverlay {
public:
	typedef QScopedPointer<HeatmapOverlay> uptr;
	typedef QSharedPointer<HeatmapOverlay> sptr;
	typedef QWeakPointer<HeatmapOverlay> wptr;

	/**
	*	Creates a new HeatmapOverlay object with a given previous module and a PixelDiff function which should be displayed.
	*
	*	@param previous The previous module of this filter.
	*	@param difference The difference that should be displayed.
	*/
	HeatmapOverlay(Module previous, model::difference::PixelDiff difference);
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
