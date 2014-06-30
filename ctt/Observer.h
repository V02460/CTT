#if !defined(_OBSERVER_H)
#define _OBSERVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {

class Observer {
public:
	typedef QScopedPointer<Observer> uptr;
	typedef QSharedPointer<Observer> sptr;
	typedef QWeakPointer<Observer> wptr;

	slot update();
};

}  // namespace model

#endif  //_OBSERVER_H
