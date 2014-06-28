


#if !defined(_MIXFILTER_H)
#define _MIXFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class MixFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_MIXFILTER_H
