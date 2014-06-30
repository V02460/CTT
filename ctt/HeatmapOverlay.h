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

	HeatmapOverlay(const Module &predecessor);
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
