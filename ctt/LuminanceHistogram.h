#ifndef _LUMINANCEHISTOGRAM_H
#define _LUMINANCEHISTOGRAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Histogram.h"
#include "Frame.h"

namespace model {
namespace frame {
namespace histogram {

/**
 * A Histogram describing the distribution of the intensity of the luminance channel in a frame.
 */
class LuminanceHistogram : public Histogram {
public:
    typedef QScopedPointer<LuminanceHistogram> uptr;
    typedef QSharedPointer<LuminanceHistogram> sptr;
    typedef QWeakPointer<LuminanceHistogram> wptr;

    /**
     * Creates a new LuminanceHistogram from a Frame containing the distribution of its luminance channel.
     *
     * @param frame Image source for the histogram calculation
     */
    explicit LuminanceHistogram(const Frame &frame);

    //virtual float getValue(unsigned int i) const Q_DECL_OVERRIDE;
    virtual HistogramType getType() const Q_DECL_OVERRIDE;

protected:
    virtual QSharedPointer<QOpenGLShader> getHistogramGridFS() Q_DECL_OVERRIDE;
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_LUMINANCEHISTOGRAM_H
