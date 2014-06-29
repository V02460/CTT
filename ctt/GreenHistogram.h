


#if !defined(_GREENHISTOGRAM_H)
#define _GREENHISTOGRAM_H

#include "Histogram.h"
#include "Frame.h"

/**
* A Histogram describing the distribution of the intensity of the green channel in a frame.
*/
class GreenHistogram : public Histogram {
public:
	/**
	* Creates a new GreenHistogram describing the distribution of the intensity of the green channel of the submitted frame.
	* @param frame the GreenHistogram will describe the distribution of the intensity of the green channel of this frame
	*/
	GreenHistogram(Frame frame);
};

#endif  //_GREENHISTOGRAM_H
