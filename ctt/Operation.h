


#if !defined(_OPERATION_H)
#define _OPERATION_H


class Operation {
public:
	virtual void do() = 0;
	virtual void undo() = 0;
private:
	Operation *next;
};

#endif  //_OPERATION_H
