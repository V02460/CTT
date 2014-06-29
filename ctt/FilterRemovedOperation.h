#if !defined(_FILTERREMOVEDOPERATION_H)
#define _FILTERREMOVEDOPERATION_H

#include "FilterListOperation.h"
#include "FilterList.h"

namespace controller {
namespace operation {

class FilterRemovedOperation : public FilterListOperation {
public:
	void FilterREmovedOperation(int index, FilterList filterList);
	void do();
	void undo();
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERREMOVEDOPERATION_H
