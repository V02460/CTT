#ifndef _MEMENTO_H
#define _MEMENTO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMap>
#include "IllegalArgumentException.h"
#include "Saveable.h"

using ::exception::IllegalArgumentException;

namespace model {
namespace saveable {

/**
 * A memento capsules a set of variables and pointers used to save and restore the state of savable objects.
 * It is only possible to save variables as strings, but casting them to different types is hidden behind the methods of
 * this class.
 * Furthermore pointers will be saved as Saveable pointer. Those two restrictions are the reason savable classes need to know
 * what variable- / pointer-types they use and use the correct method / cast to the correct pointer type.
 */
class Memento {

public:
    typedef QScopedPointer<Memento> uptr;
    typedef QSharedPointer<Memento> sptr;
    typedef QWeakPointer<Memento> wptr;

	/**
	 * Returns the pointer with the given name.
	 *
	 * @param name The name of the requested pointer.
	 * @return The pointer with given name.
	 * @throws InvalidArgumentException Is thrown if there is no pointer with given name.
	 */
	template<class T> T* getPointer(QString name) const {
		return getSharedPointer<T>(name).data();
	}

	/**
	 * Returns the shared pointer with given name.
	 *
	 * @param name The name of the requested shared pointer.
	 * @return The shared pointer with given name.
	 * @throws InvalidArgumentException Is thrown if there is no pointer with given name.
	 */
	template<class T> QSharedPointer<T> getSharedPointer(QString name) const {
		if (!pointerMap.contains(name)) {
			throw new IllegalArgumentException(QString("There is no pointer with name ").append(name).append(" in this memento."));
		}
		QSharedPointer<T> pointer = dynamic_cast<T>(pointerMap.value(name));
		if (!pointer) {
			throw new IllegalArgumentException(QString("The pointer is not of requested type."));
		}
		return pointer;
	}

	/**
	 * Creates a new, empty memento.
	 */
	Memento();

	/**
	 * Destroys the memento.
	 */
	~Memento();

    /**
     * Converts the given value to a string and adds it with the given name to the map of saved variables.
     * This method overwrites any variable with given name already saved.
     *
     * @param name The name of the variable to be saved in this memento.
	 * @param value The value of the variable to be saved in this memento.
     */
    void setBool(QString name, bool value);

    /**
     * Converts the variable with the given name, converts it to a boolean and returns it.
     *
     * @param name The name of the requested boolean.
     * @return The boolean with given name.
     * @throws InvalidArgumentException Is thrown if there is no variable with given name or the variable with given
     *     name can not be cast to a boolean.
     */
    bool getBool(QString name) const;

    /**
    * Converts the given value to a string and adds it with the given name to the map of saved variables.
    * This method overwrites any variable with given name already saved.
    *
    * @param name The name of the variable to be saved in this memento.
	* @param value The value of the variable to be saved in this memento.
    */
    void setInt(QString name, int value);

    /**
     * Converts the variable with the given name, converts it to an integer and returns it.
     *
     * @param name The name of the requested integer.
     * @return The integer with given name.
     * @throws InvalidArgumentException Is thrown if there is no variable with given name or the variable with given
     *     name can not be cast to an integer.
     */
    int getInt(QString name) const;

	/**
	* Converts the given value to a string and adds it with the given name to the map of saved variables.
	* This method overwrites any variable with given name already saved.
	*
	* @param name The name of the variable to be saved in this memento.
	* @param value The value of the variable to be saved in this memento.
	*/
	void setUInt(QString name, unsigned int value);

	/**
	* Converts the variable with the given name, converts it to an unsigned integer and returns it.
	*
	* @param name The name of the requested integer.
	* @return The unsigned integer with given name.
	* @throws IllegalArgumentException Is thrown if there is no variable with given name or the variable with given
	*     name can not be cast to an integer.
	*/
	unsigned int getUInt(QString name) const;

    /**
     * Converts the given value to a string and adds it with the given name to the map of saved variables.
     * This method overwrites any variable with given name already saved.
     *
     * @param name The name of the variable to be saved in this memento.
	 * @param value The value of the variable to be saved in this memento.
     */
    void setFloat(QString name, float value);

    /**
     * Converts the variable with the given name, converts it to a float and returns it.
     *
     * @param name The name of the requested float.
     * @return The float with given name.
     * @throws InvalidArgumentException Is thrown if there is no variable with given name or the variable with given
     *     name can not be cast to a float.
     */
    float getFloat(QString name) const;

    /**
     * Converts the given value to a string and adds it with the given name to the map of saved variables.
     * This method overwrites any variable with given name already saved.
     *
     * @param name The name of the variable to be saved in this memento.
	 * @param value The value of the variable to be saved in this memento.
     */
    void setDouble(QString name, double value);

    /**
     * Converts the variable with the given name, converts it to a double and returns it.
     *
     * @param name The name of the requested double.
     * @return The double with given name.
     * @throws InvalidArgumentException Is thrown if there is no variable with given name or the variable with given
     *     name can not be cast to a double.
     */
    double getDouble(QString name) const;

    /**
     * Adds the given string and with the given name to the map of saved variables.
     * This method overwrites any variable with given name already saved.
     *
     * @param name The name of the variable to be saved in this memento.
	 * @param value The value of the variable to be saved in this memento.
     */
    void setString(QString name, QString value);

    /**
     * Returns the string with the given name.
     *
     * @param name The name of the requested string.
     * @return The string with given name.
     * @throws InvalidArgumentException Is thrown if there is no variable with given name.
     */
    QString getString(QString name) const;

    /**
     * Saves the given shared pointer as void pointer with the given name.
     *
     * @param name The name of the shared pointer to be saved in this memento.
	 * @param pointer The shared pointer to be saved in this memento.
     */
	void setSharedPointer(QString name, QSharedPointer<Saveable>);

    /**
     * Returns the map of all variables.
     * 
     * @return The map of all variables.
     */
    QMap<QString, QString> getVariableMap() const;

    /**
     * Returns the map of all pointers.
     *
     * @return The map of all pointers.
     */
	QMap<QString, QSharedPointer<Saveable>> getPointerMap() const;

private:
	const QString TRUE_STRING = QString("true");
	const QString FALSE_STRING = QString("false");

    QMap<QString, QString> variableMap; 
	QMap<QString, QSharedPointer<Saveable>> pointerMap;
};

}  // namespace saveable
}  // namespace model

#endif  //_MEMENTO_H