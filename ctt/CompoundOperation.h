


#if !defined(_COMPOUNDOPERATION_H)
#define _COMPOUNDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Operation.h"

class CompoundOperation : public Operation {
public:
	typedef QScopedPointer<CompoundOperation> uptr;
	typedef QSharedPointer<CompoundOperation> sptr;
	typedef QWeakPointer<CompoundOperation> wptr;

	void do();
	void undo();
};

#endif  //_COMPOUNDOPERATION_H
