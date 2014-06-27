


#if !defined(_OPERATIONLIST_H)
#define _OPERATIONLIST_H

#include "Operation.h"

class OperationList {
public:
	void do(Operation operation);
	void undo();
	void redo();
	void setLastSavedState();
	bool hasSavableChanges();
	bool canUndo();
	bool canRedo();
private:
	Operation *currentOperation;
};

#endif  //_OPERATIONLIST_H
