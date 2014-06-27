


#if !defined(_RESCALEFILTER_H)
#define _RESCALEFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class RescaleFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
};

#endif  //_RESCALEFILTER_H
