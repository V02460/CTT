#ifndef _OBSERVABLE_H
#define _OBSERVABLE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Observer.h"

namespace model {

/**
 * An Observable is an Object that Observers can subscribe to, to be notified via the changed() signal when the state of
 * the Observable changes.
 *
 */
class Observable {
public:
    typedef QScopedPointer<Observable> uptr;
    typedef QSharedPointer<Observable> sptr;
    typedef QWeakPointer<Observable> wptr;

    /**
     * Subscribes the submitted Observer to the Observable, i.e. the Observer will be notified when the state of the
     * Observable changes.
     *
     * @param observer this Observer will be subscribed to the Observable.
     */
    void subscribe(Observer::sptr observer);

    /**
     * Unsubscribes the submitted Observer from the Observable, i.e. the Observer will not/no longer be notified when
     * the state of the Observable changes.
     *
     * @param observer this Observer will be unsubscribed from the Observable.
     */
    void unsubscribe(const Observer &observer);

signals:
    /**
     * this signal will be emitted when the state of the Observable changes.
     *
     */
    void changed();
};

}  // namespace model

#endif  //_OBSERVABLE_H
