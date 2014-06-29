


#if !defined(_INTEGERINTERVAL_H)
#define _INTEGERINTERVAL_H


class IntegerInterval {
public:
	IntegerInterval(int a, int b);
	bool contains(int x);
	int getStart();
	int getEnd();
	void setStart(int start);
	void setEnd(int end);
	bool canMergeWith(IntegerInterval interval);
	void mergeWith(IntegerInterval interval);
private:
	int start;
	int end;
};

#endif  //_INTEGERINTERVAL_H
