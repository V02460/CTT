#if !defined(_LUMINANCEHISTOGRAM_H)
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
	/**
	* Creates a new LuminanceHistogram describing the distribution of the intensity of the luminance channel of the submitted frame.
	* @param frame the LuminanceHistogram will describe the distribution of the intensity of the luminance channel of this frame
	*/
	LuminanceHistogram(Frame frame);
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_LUMINANCEHISTOGRAM_H
