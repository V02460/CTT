#ifndef _SAVEABLELIST_H
#define _SAVEABLELIST_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Saveable.h"
#include "Observable.h"

namespace model {
namespace saveable {

/**
 * Subscribable list for storing objects and communicating with signals and slots.
 *
 * Note that a saveable List may not contain another saveable list!
 */
template <typename T>
class SaveableList : public Saveable, public Observable {
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
    void insert(int index, typename T::sptr element);

    /**
     * Remove the list element at the given index.
     *
     * @return T Returns the removed element
     */
    typename T::sptr remove(int index);

    /**
     * Get the list element at the given index.
     *
     * @return T Returns the element at the index
     */
    const typename T::sptr get(int index) const;

	/**
	 *	Get the size of the whole list.
	 *
	 *	@return Returns the current number of elements in this list
	 */
	const int getSize() const;

	/**
	 * Returns the type of the template.
	 *
	 * @return The type of the template.
	 */
	const ::model::saveable::Saveable::SaveableType getTemplateType();

	void clear();

    virtual Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(Memento memento) Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
	static Saveable::SaveableType getSaveableType();
	virtual SaveableType saveableType() const Q_DECL_OVERRIDE;

private:
    QList<typename T::sptr> list;

	static const QString SIZE;
	static const QString TEMPLATE;
	static const QString ELEMENT;
};

}  // namespace saveable
}  // namespace model

#include "SaveableList_impl.h"

#endif  //_SAVEABLELIST_H