


#if !defined(_FILTER_H)
#define _FILTER_H

#include "Module.h"
#include "Frame.h"
#include "Memento.h"

class Filter : public Module {
public:
	bool supportsIntervals();
	void Filter();
	Map getParams();
	void setPreviousModule(Module previous);
	virtual QString getName() = 0;
	Module *nextModule;
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
private:
	Map<QString, FilterParam> parameters;
	Module *previous;
	Module *next;
};

#endif  //_FILTER_H
