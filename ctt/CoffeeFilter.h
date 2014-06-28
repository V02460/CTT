


#if !defined(_COFFEEFILTER_H)
#define _COFFEEFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class CoffeeFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_COFFEEFILTER_H
