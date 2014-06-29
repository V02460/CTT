#if !defined(_EARTHMOVERSHISTOGRAMDIFF_H)
#define _EARTHMOVERSHISTOGRAMDIFF_H

#include "FrameDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

class EarthMoversHistogramDiff : public FrameDiff {
public:
	double getDif(int frameNr);
	void FrameDif(Video video1, Video video2);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace difference
}  // namespace model

#endif  //_EARTHMOVERSHISTOGRAMDIFF_H
