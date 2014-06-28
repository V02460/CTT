


#if !defined(_MODULE_H)
#define _MODULE_H

#include "Saveable.h"
#include "Frame.h"
#include "Memento.h"

class Module : public Saveable {
public:
	virtual Frame getFrame(int frameNumber) = 0;
	List<Module> getUsesList();
	int getFrameCount();
	bool uses(Module module);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_MODULE_H
