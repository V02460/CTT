#if !defined(_OBSERVER_H)
#define _OBSERVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {

class Observer {
public:
	slot update();
};

}  // namespace model

#endif  //_OBSERVER_H
