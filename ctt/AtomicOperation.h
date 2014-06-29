#if !defined(_ATOMICOPERATION_H)
#define _ATOMICOPERATION_H

#include "Operation.h"

namespace controller {
namespace operation {

class AtomicOperation : public Operation {
public:
	void do();
	void undo();
};

}  // namespace operation
}  // namespace controller

#endif  //_ATOMICOPERATION_H
