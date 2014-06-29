


#if !defined(_BLUEHISTOGRAM_H)
#define _BLUEHISTOGRAM_H

#include "Histogram.h"
#include "Frame.h"

/**
* A Histogram describing the distribution of the intensity of the blue channel in a frame.
*/
class BlueHistogram : public Histogram {
public:
	/**
	* Creates a new BlueHistogram describing the distribution of the intensity of the blue channel of the submitted frame.
	* @param frame the BlueHistogram will describe the distribution of the intensity of the blue channel of this frame
	*/
	BlueHistogram(Frame frame);
};

#endif  //_BLUEHISTOGRAM_H
