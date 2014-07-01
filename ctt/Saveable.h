#if !defined(_Saveable_H)
#define _Saveable_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Observer.h"
#include "Memento.h"

namespace model {
namespace project {

/**
 * Objects, whose state can be externalised into a memento and restored from one.
 */
class Saveable {

public:
	typedef QScopedPointer<Saveable> uptr;
	typedef QSharedPointer<Saveable> sptr;
	typedef QWeakPointer<Saveable> wptr;

	/**
	 * The destructor of this class.
	 */
	virtual ~Saveable();

    /**
     * Gets the internal state of the object as a Memento.
     *
     * @return Memento the internal state of the object
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual Memento getMemento() const = 0;

    /**
     * Sets the internal state of the object to the state saved in a submitted Memento.
     *
     * @param memento this state will be restored
     */
	virtual void restore(Memento memento) = 0;

    /**
     * Creates and returns a dummy instance of the class with the sole purpose to have a state restored from a Memento.
     *
     * @return Saveable the dummy object
	 * @throws NotImplementedException if this method is called on a class which isn't meant to be instantiable
     */
    static Saveable::sptr getDummy();

	/**
	 * Checks whether the object is a dummy object.
	 *
	 * @return boolean true only if the object is a dummy
	 */
	bool isDummy() const;

protected:
	bool isDummy = false;
};

}  // namespace project
}  // namespace model

#endif  //_Saveable_H
