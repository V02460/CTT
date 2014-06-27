


#if !defined(_GREENHISTOGRAM_H)
#define _GREENHISTOGRAM_H

#include "Histogram.h"
#include "Frame.h"

class GreenHistogram : public Histogram, public Histogram {
public:
	void GreenHistogram(Frame frame);
};

#endif  //_GREENHISTOGRAM_H
