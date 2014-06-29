


#if !defined(_FILTERLIST_H)
#define _FILTERLIST_H

#include "Observable.h"
#include "Filter.h"
#include "Video.h"

class FilterList : public Observable, public Saveable {
public:
	void add(Filter filter, int pos);
	Filter remove(int pos);
	int getLength();
	void setPrevOfFirst(Video base);
	Filter getLast();
	QList<Filter> getQList();

	Memento getMemento();

	void restore(Memento memento);

	Saveable* getDummy();
private:
	FilterList();
	int length;
};

#endif  //_FILTERLIST_H
