


#if !defined(_GREYSCALEFILTER_H)
#define _GREYSCALEFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class GreyscaleFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
};

#endif  //_GREYSCALEFILTER_H
