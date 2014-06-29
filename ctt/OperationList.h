#if !defined(_OPERATIONLIST_H)
#define _OPERATIONLIST_H

#include "Operation.h"

namespace controller {
namespace operation {

class OperationList {
public:
	void do(Operation operation);
	void undo();
	void redo();
	void setLastSavedState();
	bool hasSaveableChanges();
	bool canUndo();
	bool canRedo();
private:
	Operation *currentOperation;
};

}  // namespace operation
}  // namespace controller

#endif  //_OPERATIONLIST_H
