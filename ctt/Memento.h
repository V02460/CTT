#ifndef _MEMENTO_H
#define _MEMENTO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMap>
#include <QVariant>

namespace model {
namespace saveable {

/**
 * A memento capsules a set of variables and pointers used to save and restore the state of savable objects.
 * It uses QVariants to save variables. Furthermore pointers will be saved as void pointer. Those two restrictions
 * are the reason savable classes need to know what variable- / pointer-types they use and use the correct method / cast to the correct pointer type.
 */
class Memento {

public:
    typedef QScopedPointer<Memento> uptr;
    typedef QSharedPointer<Memento> sptr;
    typedef QWeakPointer<Memento> wptr;

    /**
     * Adds the given pair of name and value to a map.
     * This method overwrites any variable with given name already saved.
     *
     * @param value The value of the variable to be saved in this memento.
     * @param name The name of the variable to be saved in this memento.
     */
	void setVariable(QString name, QVariant value);

    /**
     * Returns the variable with given name.
     *
     * @param name The name of the requested variable.
     * @return The variable with given name.
     * @throws InvalidArgumentException Is thrown if there is no variable with given name.
     */
    QVariant getVariable(QString name) const;

    /**
     * Saves the given pointer as void pointer with the given name.
     *
     * @param pointer The pointer to be saved in this memento.
     * @param name The name of the pointer to be saved in this memento.
     */
    void setPointer(QString name, void *pointer);

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
    QMap<QString, QVariant> getVariableMap() const;

    /**
     * Returns the map of all pointers.
     *
     * @return The map of all pointers.
     */
    QMap<QString, void*> getPointerMap() const;

private:
    QMap<QString, QVariant> variableMap;
    QMap<QString, void*> pointerMap;
};

}  // namespace saveable
}  // namespace model

#endif  //_MEMENTO_H
