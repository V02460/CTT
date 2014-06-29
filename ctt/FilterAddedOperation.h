#if !defined(_FILTERADDEDOPERATION_H)
#define _FILTERADDEDOPERATION_H

#include "FilterListOperation.h"
#include "Filter.h"
#include "FilterList.h"

namespace controller {
namespace operation {

class FilterAddedOperation : public FilterListOperation {
public:
	void FilterAddedOperation(Filter filter, FilterList filterList);
	void do();
	void undo();
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERADDEDOPERATION_H
