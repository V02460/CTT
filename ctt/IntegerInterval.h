


#if !defined(_INTEGERINTERVAL_H)
#define _INTEGERINTERVAL_H


class IntegerInterval {
public:
	void IntegerInterval(int a, int b);
	bool contains(int x);
	int getStart();
	int getEnd();
	void setStart(int start);
	void setEnd(int end);
private:
	int start;
	int end;
};

#endif  //_INTEGERINTERVAL_H
