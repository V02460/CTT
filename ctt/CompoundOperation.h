#if !defined(_COMPOUNDOPERATION_H)
#define _COMPOUNDOPERATION_H

#include "Operation.h"

namespace controller {
namespace operation {

class CompoundOperation : public Operation {
public:
	void do();
	void undo();
};

}  // namespace operation
}  // namespace controller

#endif  //_COMPOUNDOPERATION_H
