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
	*	@param predecessor The previous module of this filter.
	*	@param difference The difference that should be displayed.
	*/
	HeatmapOverlay(const Module &predecessor, model::difference::PixelDiff::sptr difference);
	virtual ~HeatmapOverlay();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
private:
	PixelDiff::uptr data;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_HEATMAPOVERLAY_H
