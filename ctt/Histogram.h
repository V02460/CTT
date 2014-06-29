


#if !defined(_HISTOGRAM_H)
#define _HISTOGRAM_H

#include "HistogramType.h"

/**
 * A Histogram with 256 values describing the intensity distribution of a channel in a frame.
 *
 */
class Histogram {
public:
    /**
     * Gets the value for the entry with the number i.
     *
     * @param i the value of this entry will be returned
     * @return float the value for the entry with the number i
	 * @throws Invalid
     */
    float getValue(unsigned int i);

    /**
     * Gets the type of the histogram, specifying the type of variable the histogram describes the distribution of. 
     *
     * @return HistogramType the type of the histogram
     */
    virtual HistogramType getType();

protected:
	float values[256];/**< The values of the histogram */
};

#endif  //_HISTOGRAM_H
