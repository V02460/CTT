


#if !defined(_OPERATION_H)
#define _OPERATION_H

/**
*	The Operation is providing functionality for doing and undoing methods which trigger a change in the underlying model.
**/
class Operation {
public:
	/**
	*	Manages doing the Operation specified in this class.
	**/
	virtual void doOperation() = 0;

	/**
	*	Manages undoing the Operation specified in this class.
	**/
	virtual void undoOperation() = 0;
private:
	Operation *next;
};

#endif  //_OPERATION_H
