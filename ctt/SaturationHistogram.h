#ifndef _SATURATIONHISTOGRAM_H
#define _SATURATIONHISTOGRAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Histogram.h"
#include "Frame.h"

namespace model {
namespace frame {
namespace histogram {

/**
 * A Histogram describing the distribution of the intensity of the saturation channel in a frame.
 */
class SaturationHistogram : public Histogram {
public:
	typedef QScopedPointer<SaturationHistogram> uptr;
	typedef QSharedPointer<SaturationHistogram> sptr;
	typedef QWeakPointer<SaturationHistogram> wptr;

    /**
     * Creates a new SaturationHistogram from a Frame containing the distribution of its saturation channel.
     *
     * @param frame Image source for the histogram calculation
     */
    explicit SaturationHistogram(const Frame &imageData);

    //virtual float getValue(unsigned int i) const Q_DECL_OVERRIDE;
    virtual HistogramType getType() const Q_DECL_OVERRIDE;

protected:
    virtual QString getGridFSFilePath() const  Q_DECL_OVERRIDE;
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_SATURATIONHISTOGRAM_H
