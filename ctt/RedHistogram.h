#ifndef _REDHISTOGRAM_H
#define _REDHISTOGRAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Histogram.h"
#include "Frame.h"

namespace model {
namespace frame {
namespace histogram {

/**
 * A Histogram describing the distribution of the intensity of the red channel in a frame.
 */
class RedHistogram : public Histogram {
public:
    typedef QScopedPointer<RedHistogram> uptr;
    typedef QSharedPointer<RedHistogram> sptr;
    typedef QWeakPointer<RedHistogram> wptr;

    /**
     * Creates a new RedHistogram from a Frame containing the distribution of its red channel.
     *
     * @param frame Image source for the histogram calculation
     */
    explicit RedHistogram(const Surface &frame);

    //virtual float getValue(unsigned int i) const Q_DECL_OVERRIDE;
    virtual HistogramType getType() const Q_DECL_OVERRIDE;

protected:
    virtual QString getGridFSFilePath() const  Q_DECL_OVERRIDE;
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_REDHISTOGRAM_H
