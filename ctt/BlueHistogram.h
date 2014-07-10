#ifndef _BLUEHISTOGRAM_H
#define _BLUEHISTOGRAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Histogram.h"
#include "Frame.h"

namespace model {
namespace frame {
namespace histogram {

/**
 * A Histogram describing the distribution of the intensity of the blue channel in a frame.
 * Requires an active context.
 */
class BlueHistogram : public Histogram {
public:
    typedef QScopedPointer<BlueHistogram> uptr;
    typedef QSharedPointer<BlueHistogram> sptr;
    typedef QWeakPointer<BlueHistogram> wptr;

    /**
    * Creates a new BlueHistogram describing the distribution of the intensity of the blue channel of the submitted
    * frame.
    *
    * @param frame the BlueHistogram will describe the distribution of the intensity of the blue channel of this frame
    */
    explicit BlueHistogram(const Frame &frame);

    //virtual float getValue(unsigned int i) const Q_DECL_OVERRIDE;
    virtual HistogramType getType() const Q_DECL_OVERRIDE;

protected:
    QSharedPointer<QOpenGLShaderProgram> createHistogramGridShaderProgram();
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_BLUEHISTOGRAM_H
