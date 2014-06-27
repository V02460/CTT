


#if !defined(_COMPOUNDOPERATION_H)
#define _COMPOUNDOPERATION_H

#include "Operation.h"

class CompoundOperation : public Operation {
public:
	void do();
	void undo();
};

#endif  //_COMPOUNDOPERATION_H
