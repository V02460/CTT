


#if !defined(_MODULE_H)
#define _MODULE_H

#include "Savable.h"
#include "Frame.h"
#include "Memento.h"

class Module : public Savable {
public:
	virtual Frame getFrame(int frameNumber) = 0;
	List<Module> getUsesList();
	int getFrameCount();
	bool uses(Module module);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
};

#endif  //_MODULE_H
