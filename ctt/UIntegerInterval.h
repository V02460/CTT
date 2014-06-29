
#include "Saveable.h"

#if !defined(_INTEGERINTERVAL_H)
#define _INTEGERINTERVAL_H


class UIntegerInterval: public Saveable {
public:
	UIntegerInterval(unsigned int a, unsigned int b);
	bool contains(unsigned int x);
	int getStart();
	int getEnd();
	void setStart(unsigned int start);
	void setEnd(unsigned int end);
	bool canMergeWith(UIntegerInterval interval);
	void mergeWith(UIntegerInterval interval);

	Memento getMemento();

	void restore(Memento memento);

	static Saveable* getDummy();
private:
	UIntegerInterval();
	unsigned int start;
	unsigned int end;
};

#endif  //_INTEGERINTERVAL_H
