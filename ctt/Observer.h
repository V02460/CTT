#if !defined(_OBSERVER_H)
#define _OBSERVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

namespace model {

/**
 * An Observer can be subscribed to an Observable to be notified via a signal to the update() slot when the state of the
 * Observable changes.
 *
 */
class Observer : public QObject {
public:
    typedef QScopedPointer<Observer> uptr;
    typedef QSharedPointer<Observer> sptr;
    typedef QWeakPointer<Observer> wptr;

public slots:
    /**
     * This slot is meant to be used to notify the Observer of changes of the state of the Object it observes. 
     *
     */
    virtual void update();
};

}  // namespace model

#endif  //_OBSERVER_H
