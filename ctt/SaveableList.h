


#if !defined(_SAVEABLELIST_H)
#define _SAVEABLELIST_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Saveable.h"
#include "Observable.h"

template < Saveable E >
class SaveableList : public Saveable, public Observable {
public:
	typedef QScopedPointer<SaveableList> uptr;
	typedef QSharedPointer<SaveableList> sptr;
	typedef QWeakPointer<SaveableList> wptr;

	void insert(uint index, E element);
	E remove(uint index);
	E get(uint index);

private: 
	E firstElement;
};

#endif  //_SAVEABLELIST_H