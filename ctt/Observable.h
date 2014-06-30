


#if !defined(_OBSERVABLE_H)
#define _OBSERVABLE_H

#include "Observer.h"
#include "QObject"

/**
 * An Object that Observers can subscribe to, to be notified when the state of the Observable changes.
 *
 */
class Observable: public QObject {
public:
    /**
     * Subscribes the submitted Observer to the Observable, i.e. the Observer will be notified when the state of the Observable changes.
     *
     * @param observer this Observer will be subscribed to the Observable.
     */
    void subscribe(Observer observer);

    /**
     * Unsubscribes the submitted Observer from the Observable, i.e. the Observer will not/no longer be notified when the state of the Observable changes.
     *
     * @param observer this Observer will be unsubscribed from the Observable.
     */
    void unsubscribe(Observer observer);

signals:
    /**
     * this signal will be emitted when the state of the Observable changes.
     *
     */
    void changed();
};

#endif  //_OBSERVABLE_H
