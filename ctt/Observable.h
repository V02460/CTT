


#if !defined(_OBSERVABLE_H)
#define _OBSERVABLE_H

#include "Observer.h"

class Observable {
public:
	signal changed();
	void subscribe(Observer observer);
	void unsubscribe(Observer observer);
};

#endif  //_OBSERVABLE_H
