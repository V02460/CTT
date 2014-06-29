#if !defined(_OBSERVABLE_H)
#define _OBSERVABLE_H

#include "Observer.h"

namespace model {

class Observable {
public:
	signal changed();
	void subscribe(Observer observer);
	void unsubscribe(Observer observer);
};

}  // namespace model

#endif  //_OBSERVABLE_H
