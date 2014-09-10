#ifndef _EARTHMOVERSHISTOGRAMDIFF_H
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

    static const QMap<::model::frame::histogram::Histogram::HistogramType, QByteArray> kDiffIDs;

    /**
     * Creates a new EarthMoversHistogramDiff using the histograms of the submitted type to calculate earth mover's
     * distances between frames of the two submitted videos.
     *
     * @param type the type of histogram that will be used for the calculations
     * @param video1 the first of the two videos the EarthMoversHistogramDiff will compare 
     * @param video2 the second of the two videos the EarthMoversHistogramDiff will compare
     */
    EarthMoversHistogramDiff(::model::frame::histogram::Histogram::HistogramType type,
                             ::model::video::Video::sptr video1,
                             ::model::video::Video::sptr video2);

    virtual ~EarthMoversHistogramDiff();

    virtual QString getName() const Q_DECL_OVERRIDE;

    virtual double getDiff(unsigned int frameNr) Q_DECL_OVERRIDE;

	virtual model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
	virtual void restore(model::saveable::Memento memento) Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
	static Saveable::SaveableType getSaveableType() { return Saveable::earthMoversHistogramDiff; }
	virtual SaveableType saveableType() const Q_DECL_OVERRIDE { return getSaveableType(); }

private:
	Q_DISABLE_COPY(EarthMoversHistogramDiff)

	static const QString kVideo1Str;
	static const QString kVideo2Str;
	static const QString kTypeStr;

    EarthMoversHistogramDiff();

	void calculateDiff(unsigned int frameNr);

	model::frame::Histogram::HistogramType type;
	QMap<unsigned int, double> diff;
};

}  // namespace difference
}  // namespace model

#endif  //_EARTHMOVERSHISTOGRAMDIFF_H
