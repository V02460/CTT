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

	double getDif(int frameNr);
	void FrameDif(Video video1, Video video2);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace difference
}  // namespace model

#endif  //_EARTHMOVERSHISTOGRAMDIFF_H
