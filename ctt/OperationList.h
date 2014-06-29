


#if !defined(_OPERATIONLIST_H)
#define _OPERATIONLIST_H

#include "Operation.h"

/**
*	The OperationList contains a list with every Operation executed since the last load of the Project and the functionality to do, undo and redo those Operations.
**/
class OperationList {
public:

	/**
	*	Manages doing the given Operation.
	*	@param operation The Operation that should be done.
	**/
	void doOperation(Operation operation);

	/**
	*	Manages undoing the Operation that has been done previously.
	**/
	void undoOperation();

	/**
	*	Manages redoing the Operation that has been undone previously.
	**/
	void redoOperation();

	/**
	*	Sets the last state of the Project which has been saved.
	**/
	void setLastSavedState();

	/**
	*	Determines whether there are actual changes since the last saved state.
	**/
	bool hasSaveableChanges();

	/**
	*	Determines whether an Operation has been done previously, making it possible to execute undoOperation.
	**/
	bool canUndo();

	/**
	*	Determines whether an Operation has been undone previously, making it possible to execute redoOperation.
	**/
	bool canRedo();
private:
	Operation *currentOperation;
};

#endif  //_OPERATIONLIST_H
