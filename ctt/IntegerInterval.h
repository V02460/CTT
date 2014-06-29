


#if !defined(_INTEGERINTERVAL_H)
#define _INTEGERINTERVAL_H


class IntegerInterval: public Saveable {
public:
	IntegerInterval(int a, int b);
	bool contains(int x);
	int getStart();
	int getEnd();
	void setStart(int start);
	void setEnd(int end);
	bool canMergeWith(IntegerInterval interval);
	void mergeWith(IntegerInterval interval);

	Memento getMemento();

	void restore(Memento memento);

	static Saveable* getDummy();
private:
	IntegerInterval();
	int start;
	int end;
};

#endif  //_INTEGERINTERVAL_H
