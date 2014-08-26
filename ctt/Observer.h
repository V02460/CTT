#ifndef _OBSERVER_H
#define _OBSERVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

namespace model {

/**
 * An Observer can be subscribed to an Observable to be notified via a update() method when the state of the
 * Observable changes.
 *
 */
class Observer {

public:
    typedef QScopedPointer<Observer> uptr;
    typedef QSharedPointer<Observer> sptr;
    typedef QWeakPointer<Observer> wptr;

    virtual ~Observer();

    /**
     * This method is meant to be used to notify the Observer of changes of the state of the Object it observes.
     */
    virtual void update();
};

}  // namespace model

#endif  //_OBSERVER_H
