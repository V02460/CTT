


#if !defined(_TIMESHIFTFILTER_H)
#define _TIMESHIFTFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class TimeshiftFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
};

#endif  //_TIMESHIFTFILTER_H
