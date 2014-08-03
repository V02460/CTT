#ifndef _SAVEABLE_H
#define _SAVEABLE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Observer.h"

//#include "Memento.h"
namespace model {
namespace saveable {
    class Memento;
}}


namespace model {
namespace saveable {

/**
 * Objects, whose state can be externalized into a memento and restored from one.
 */
class Saveable {

public:
	typedef QScopedPointer<Saveable> uptr;
	typedef QSharedPointer<Saveable> sptr;
	typedef QWeakPointer<Saveable> wptr;

	/**
	 * The destructor of this class.
	 */
    virtual ~Saveable() = 0 {} // must have an implementation (linking errors, probably MOC)

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
	 * @throws IllegalArgumentException if the memento doesn't contain the data the object requires to restore itself
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

	/**
	 * Labels for the different saveables.
	 *
	 * This enum must be similar in quantity and order to the SAVEABLE_TYPE_STRINGS list. 
	 */
	enum SaveableType {
		FileVideo,
		FilteredVideo,
		Player,
		Diff,
		View,
		List
	};

	/** A string representation for the FileVideo class. */
	static const QString FILE_VIDEO;
	/** A string representation for the FilteredVideo class. */
	static const QString FILTERED_VIDEO;
	/** A string representation for the Player class. */
	static const QString PLAYER;
	/** A string representation for the FrameDiff class. */
	static const QString DIFF;
	/** A string representation for the ViewState class. */
	static const QString VIEW;
	/** A string representation for the SaveableList class. */
	static const QString LIST;

	/**
	 * A list of string representations for saveable classes.
	 *
	 * This list must be similar in quantity and order to the SavableType enum. 
	 */
	static const QList<QString> SAVEABLE_TYPE_STRINGS;

	/*
	 * Gets the type of the savable object.
	 *
	 * @return The type of the histogram
	 */
	//virtual SaveableType getType() const = 0;

protected:
	bool isDummyFlag = false;
};

}  // namespace savable
}  // namespace model

#endif  //_Saveable_H
