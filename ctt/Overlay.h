


#if !defined(_OVERLAY_H)
#define _OVERLAY_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class Overlay : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
};

#endif  //_OVERLAY_H
