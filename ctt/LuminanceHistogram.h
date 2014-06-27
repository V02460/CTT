


#if !defined(_LUMINANCEHISTOGRAM_H)
#define _LUMINANCEHISTOGRAM_H

#include "Histogram.h"
#include "Frame.h"

class LuminanceHistogram : public Histogram {
public:
	void LuminanceHistogram(Frame frame);
};

#endif  //_LUMINANCEHISTOGRAM_H
