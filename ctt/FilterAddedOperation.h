


#if !defined(_FILTERADDEDOPERATION_H)
#define _FILTERADDEDOPERATION_H

#include "FilterListOperation.h"
#include "Filter.h"
#include "FilterList.h"

class FilterAddedOperation : public FilterListOperation {
public:
	void FilterAddedOperation(Filter filter, FilterList filterList);
	void do();
	void undo();
};

#endif  //_FILTERADDEDOPERATION_H
