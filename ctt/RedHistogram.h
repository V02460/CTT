


#if !defined(_REDHISTOGRAM_H)
#define _REDHISTOGRAM_H

#include "Histogram.h"
#include "Frame.h"

/**
 * A Histogram describing the distribution of the intensity of the red channel in a frame.
 */
class RedHistogram : public Histogram {
public:
	/**
	 * Creates a new RedHistogram describing the distribution of the intensity of the red channel of the submitted frame.
	 * @param frame the RedHistogram will describe the distribution of the intensity of the red channel of this frame
	 */
	RedHistogram(Frame frame);
};

#endif  //_REDHISTOGRAM_H
