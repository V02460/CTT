


#if !defined(_ATOMICOPERATION_H)
#define _ATOMICOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Operation.h"

class AtomicOperation : public Operation {
public:
	typedef QScopedPointer<AtomicOperation> uptr;
	typedef QSharedPointer<AtomicOperation> sptr;
	typedef QWeakPointer<AtomicOperation> wptr;

	void do();
	void undo();
};

#endif  //_ATOMICOPERATION_H
