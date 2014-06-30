#if !defined(_EARTHMOVERSHISTOGRAMDIFF_H)
#define _EARTHMOVERSHISTOGRAMDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "FrameDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

class EarthMoversHistogramDiff : public FrameDiff {
public:
	typedef QScopedPointer<EarthMoversHistogramDiff> uptr;
	typedef QSharedPointer<EarthMoversHistogramDiff> sptr;
	typedef QWeakPointer<EarthMoversHistogramDiff> wptr;

	EarthMoversHistogramDiff(const video::Video &video1, const video::Video &video2);
	virtual ~EarthMoversHistogramDiff();

	virtual double getDiff(unsigned int frameNr) const;
};

}  // namespace difference
}  // namespace model

#endif  //_EARTHMOVERSHISTOGRAMDIFF_H
