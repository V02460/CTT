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

/**
 * Calculates distances between frames of Videos using earth mover's distance on their channel intensity histograms.
 */

class EarthMoversHistogramDiff : public FrameDiff {
public:
    typedef QScopedPointer<EarthMoversHistogramDiff> uptr;
    typedef QSharedPointer<EarthMoversHistogramDiff> sptr;
    typedef QWeakPointer<EarthMoversHistogramDiff> wptr;

    /**
     * Creates a new EarthMoversHistogramDiff using the histograms of the submitted type to calculate earth mover's
     * distances between frames of the two submitted videos.
     *
     * @param type the type of histogram that will be used for the calculations
     * @param video1 the first of the two videos the EarthMoversHistogramDiff will compare 
     * @param video2 the second of the two videos the EarthMoversHistogramDiff will compare
     */
    EarthMoversHistogramDiff(::model::frame::histogram::HistogramType type,
                             ::model::video::Video::sptr video1,
                             ::model::video::Video::sptr video2);

    virtual ~EarthMoversHistogramDiff();

    virtual double getDiff(unsigned int frameNr) const;
};

}  // namespace difference
}  // namespace model

#endif  //_EARTHMOVERSHISTOGRAMDIFF_H
