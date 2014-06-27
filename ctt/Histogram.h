


#if !defined(_HISTOGRAM_H)
#define _HISTOGRAM_H

#include "HistogramType.h"

class Histogram {
public:
	float getValue(int i);
	HistogramType getType();
private:
	float[] values;
};

#endif  //_HISTOGRAM_H
