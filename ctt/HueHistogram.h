#ifndef _HUEHISTOGRAM_H
#define _HUEHISTOGRAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Histogram.h"
#include "Frame.h"

namespace model {
namespace frame {
namespace histogram {

/**
 * A Histogram describing the distribution of the intensity of the hue channel in a frame.
 */
class HueHistogram : public Histogram {
public:
    typedef QScopedPointer<HueHistogram> uptr;
    typedef QSharedPointer<HueHistogram> sptr;
    typedef QWeakPointer<HueHistogram> wptr;

    /**
     * Creates a new HueHistogram from a Frame containing the distribution of its hue channel.
     *
     * @param frame Image source for the histogram calculation
     */
    explicit HueHistogram(Surface::sptr frame);

    //virtual float getValue(unsigned int i) const Q_DECL_OVERRIDE;
    virtual HistogramType getType() const Q_DECL_OVERRIDE;

protected:
    virtual QString getGridFSFilePath() const  Q_DECL_OVERRIDE;
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_HUEHISTOGRAM_H
