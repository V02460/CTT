#if !defined(_SAVEABLELIST_H)
#define _SAVEABLELIST_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Saveable.h"
#include "Observable.h"

namespace model {

/**
 * Subscribable list for storing objects and communicating with signals and slots.
 */
template <class T>
class SaveableList : public project::Saveable, public Observable {
public:
    typedef QScopedPointer<SaveableList> uptr;
    typedef QSharedPointer<SaveableList> sptr;
    typedef QWeakPointer<SaveableList> wptr;

    /**
     * Creates a new empty list.
     */
    SaveableList();

    /**
     * Add the element at the given index into the list.
     */
    void insert(unsigned int index, typename T::sptr element);

    /**
     * Remove the list element at the given index.
     *
     * @return T Returns the removed element
     */
    typename T::sptr remove(unsigned int index);

    /**
     * Get the list element at the given index.
     *
     * @return T Returns the element at the index
     */
    const T &get(unsigned int index) const;

    virtual project::Memento getMemento() const;
    virtual void restore(project::Memento memento);
    static project::Saveable::sptr getDummy();

private: 
    T *firstElement;
    QList<typename T::sptr> list;
};

}  // namespace model

#endif  //_SAVEABLELIST_H