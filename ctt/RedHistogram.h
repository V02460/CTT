#if !defined(_REDHISTOGRAM_H)
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
	 * Creates a new RedHistogram describing the distribution of the intensity of the red channel of the submitted
	 * frame.
	 *
	 * @param frame the RedHistogram will describe the distribution of the intensity of the red channel of this frame
	 */
	RedHistogram(Frame frame);

	virtual HistogramType getType() const;
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_REDHISTOGRAM_H
