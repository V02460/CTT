


#if !defined(_ATOMICOPERATION_H)
#define _ATOMICOPERATION_H

#include "Operation.h"

class AtomicOperation : public Operation {
public:
	void do();
	void undo();
};

#endif  //_ATOMICOPERATION_H
