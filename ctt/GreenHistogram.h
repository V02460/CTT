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
    * Creates a new GreenHistogram describing the distribution of the intensity of the green channel of the submitted
    * frame.
    *
    * @param frame the GreenHistogram will describe the distribution of the intensity of the green channel of this frame
    */
    explicit GreenHistogram(const Frame &frame);

    //virtual float getValue(unsigned int i) const Q_DECL_OVERRIDE;
    virtual HistogramType getType() const Q_DECL_OVERRIDE;

protected:
    QSharedPointer<QOpenGLShaderProgram> createHistogramGridShaderProgram();
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_GREENHISTOGRAM_H
