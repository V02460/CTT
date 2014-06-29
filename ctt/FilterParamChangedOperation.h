#if !defined(_FILTERPARAMCHANGEDOPERATION_H)
#define _FILTERPARAMCHANGEDOPERATION_H

#include "FilterListOperation.h"
#include "FilterParam.h"
#include "FilterList.h"
#include "Filter.h"

namespace controller {
namespace operation {

class FilterParamChangedOperation : public FilterListOperation {
public:
	FilterParam newParam;
	FilterParamChangedOperation(FilterParam newParam, FilterList filterList);
	void do();
	void undo();
private:
	Filter* filter;
	FilterParam oldParam;
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERPARAMCHANGEDOPERATION_H
