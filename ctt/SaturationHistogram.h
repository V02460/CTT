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
	 * Creates a new SaturationHistogram describing the distribution of the intensity of the saturation channel of the submitted frame.
	 * @param frame the SaturationHistogram will describe the distribution of the intensity of the saturation channel of this frame
	 */
    explicit SaturationHistogram(const Frame &frame);

    //virtual float getValue(unsigned int i) const Q_DECL_OVERRIDE;
    virtual HistogramType getType() const Q_DECL_OVERRIDE;

protected:
    QSharedPointer<QOpenGLShaderProgram> createHistogramGridShaderProgram();
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_SATURATIONHISTOGRAM_H
