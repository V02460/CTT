


#if !defined(_FILTERREMOVEDOPERATION_H)
#define _FILTERREMOVEDOPERATION_H

#include "FilterListOperation.h"
#include "FilterList.h"

class FilterRemovedOperation : public FilterListOperation {
public:
	void FilterREmovedOperation(int index, FilterList filterList);
	void do();
	void undo();
};

#endif  //_FILTERREMOVEDOPERATION_H
