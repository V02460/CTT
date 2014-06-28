


#if !defined(_Saveable_H)
#define _Saveable_H

#include "Observer.h"
#include "Memento.h"

/**
 * Objects, whose state can be externalised into a memento and restored from one.
 *
 */
class Saveable {

public:

    /**
     * Gets the internal state of the object as a Memento.
     *
     * @return Memento the internal state of the object
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual Memento getMemento();

    /**
     * Sets the internal state of the object to the state saved in a submitted Memento.
     *
     * @param memento this state will be restored
     */
    virtual void restore(Memento memento);

    /**
     * Creates and returns a dummy instance of the class with the sole purpose to have a state restored from a Memento.
     *
     * @return Saveable the dummy object
	 * @throws NotImplementedException if this method is called on a class which isn't meant to be instantiable
     */
    static Saveable* getDummy();

	/**
	 * Checks whether the object is a dummy object.
	 *
	 * @return boolean true only if the object is a dummy
	 */
	virtual boolean isDummy();

protected:
	boolean is_dummy;
};

#endif  //_Saveable_H
