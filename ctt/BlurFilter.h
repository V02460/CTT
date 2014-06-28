


#if !defined(_BLURFILTER_H)
#define _BLURFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class BlurFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_BLURFILTER_H
