#ifndef _GREENHISTOGRAM_H
#define _GREENHISTOGRAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Histogram.h"
#include "Frame.h"

namespace model {
namespace frame {
namespace histogram {

/**
* A Histogram describing the distribution of the intensity of the green channel in a frame.
*/
class GreenHistogram : public Histogram {
public:
    typedef QScopedPointer<GreenHistogram> uptr;
    typedef QSharedPointer<GreenHistogram> sptr;
    typedef QWeakPointer<GreenHistogram> wptr;

    /**
     * Creates a new GreenHistogram from a Frame containing the distribution of its green channel.
     *
     * @param frame Image source for the histogram calculation
     */
    explicit GreenHistogram(const Surface &frame);

    //virtual float getValue(unsigned int i) const Q_DECL_OVERRIDE;
    virtual HistogramType getType() const Q_DECL_OVERRIDE;

protected:
    virtual QString getGridFSFilePath() const  Q_DECL_OVERRIDE;;
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_GREENHISTOGRAM_H
