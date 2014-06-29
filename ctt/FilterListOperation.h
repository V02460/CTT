#if !defined(_FILTERLISTOPERATION_H)
#define _FILTERLISTOPERATION_H

#include "Operation.h"
#include "Filter.h"
#include "FilterList.h"

namespace controller {
namespace operation {

class FilterListOperation : public Operation {
public:
	void do();
	void undo();
private:
	Filter filter;
	int index;
	FilterList filterList;
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERLISTOPERATION_H
