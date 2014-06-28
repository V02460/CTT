


#if !defined(_NOISEFILTER_H)
#define _NOISEFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class NoiseFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_NOISEFILTER_H
