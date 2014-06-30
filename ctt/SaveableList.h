#if !defined(_SAVEABLELIST_H)
#define _SAVEABLELIST_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Saveable.h"
#include "Observable.h"

namespace model {

template < Saveable T >
class SaveableList : public Saveable, public Observable {
public:
	typedef QScopedPointer<SaveableList> uptr;
	typedef QSharedPointer<SaveableList> sptr;
	typedef QWeakPointer<SaveableList> wptr;

	void insert(uint index, T element);
	T remove(uint index);
	T get(uint index);

private: 
	T firstElement;
};

}  // namespace model

#endif  //_SAVEABLELIST_H