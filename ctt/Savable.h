


#if !defined(_SAVABLE_H)
#define _SAVABLE_H

#include "Observer.h"
#include "Memento.h"

class Savable : public Observer {
public:
	virtual Memento getMemento() = 0;
	virtual void restore(Memento memento) = 0;
	virtual Savable* getDummy() = 0;
};

#endif  //_SAVABLE_H
