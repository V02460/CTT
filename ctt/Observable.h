#if !defined(_OBSERVABLE_H)
#define _OBSERVABLE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Observer.h"

namespace model {

class Observable {
public:
	typedef QScopedPointer<Observable> uptr;
	typedef QSharedPointer<Observable> sptr;
	typedef QWeakPointer<Observable> wptr;

	signal changed();
	void subscribe(Observer observer);
	void unsubscribe(Observer observer);
};

}  // namespace model

#endif  //_OBSERVABLE_H
