#ifndef _MEMENTO_H
#define _MEMENTO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMap>

namespace model {
namespace saveable {

/**
 * A memento capsules a set of variables and pointers used to save and restore the state of savable objects.
 * It is only possible to save variables as strings, but casting them to different types is hidden behind the methods of
 * this class.
 * Furthermore pointers will be saved as void pointer. Those two restrictions are the reason savable classes need to know
 * what variable- / pointer-types they use and use the correct method / cast to the correct pointer type.
 */
class Memento {

public:
    typedef QScopedPointer<Memento> uptr;
    typedef QSharedPointer<Memento> sptr;
    typedef QWeakPointer<Memento> wptr;

    /**
     * Converts the given value to a string and adds it with the given name to the map of saved variables.
     * This method overwrites any variable with given name already saved.
     *
     * @param value The value of the variable to be saved in this memento.
     * @param name The name of the variable to be saved in this memento.
     */
    void setBool(bool value, QString name);

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
    * @param value The value of the variable to be saved in this memento.
    * @param name The name of the variable to be saved in this memento.
    */
    void setInt(int value, QString name);

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
     * @param value The value of the variable to be saved in this memento.
     * @param name The name of the variable to be saved in this memento.
     */
    void setFloat(float value, QString name);

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
     * @param value The value of the variable to be saved in this memento.
     * @param name The name of the variable to be saved in this memento.
     */
    void setDouble(double value, QString name);

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
     * @param value The value of the variable to be saved in this memento.
     * @param name The name of the variable to be saved in this memento.
     */
    void setString(QString value, QString name);

    /**
     * Returns the string with the given name.
     *
     * @param name The name of the requested string.
     * @return The string with given name.
     * @throws InvalidArgumentException Is thrown if there is no variable with given name.
     */
    QString getString(QString name) const;

    /**
     * Saves the given pointer as void pointer with the given name.
     *
     * @param pointer The pointer to be saved in this memento.
     * @param name The name of the pointer to be saved in this memento.
     */
    void setPointer(void *pointer, QString name);

    /**
     * Returns the pointer with the given name.
     *
     * @param name The name of the requested pointer.
     * @return The pointer with given name.
     * @throws InvalidArgumentException Is thrown if there is no pointer with given name.
     */
    void *getPointer(QString name) const;

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
    QMap<QString, void*> getPointerMap() const;

private:
    QMap<QString, QString> variableMap;
    QMap<QString, void*> pointerMap;
};

}  // namespace saveable
}  // namespace model

#endif  //_MEMENTO_H
