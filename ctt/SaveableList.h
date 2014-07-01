#if !defined(_SAVEABLELIST_H)
#define _SAVEABLELIST_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Saveable.h"
#include "Observable.h"

namespace model {

/**
 * Subscribeable list for storing objects and communicating with signals and slots.
 */
template < class T >
class SaveableList : public Saveable, public Observable, public QObject {
    Q_OBJECT
public:
    typedef QScopedPointer<SaveableList> uptr;
    typedef QSharedPointer<SaveableList> sptr;
    typedef QWeakPointer<SaveableList> wptr;

    /**
     * Creates a new empty list.
     */
    SaveableList()

    /**
     * Add the element at the given index into the list.
     */
    void insert(unsigned int index, T element);

    /**
     * Remove the list element at the given index.
     *
     * @return T Returns the removed element
     */
    T remove(unsigned int index);

    /**
     * Get the list element at the given index.
     *
     * @return T Returns the element at the index
     */
    T get(unsigned int index);

private: 
    T firstElement;
    QList<T> list;
};

}  // namespace model

#endif  //_SAVEABLELIST_H