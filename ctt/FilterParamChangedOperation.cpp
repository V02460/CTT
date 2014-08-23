#include "FilterParamChangedOperation.h"

namespace controller {
namespace operation {

using ::model::filter::Filter;
using ::model::filter::FilterParam;

FilterParamChangedOperation::FilterParamChangedOperation(FilterParam::sptr param, Filter::sptr filter)
	: param(param), filter(filter), memento(filter->getMemento()) {}

void FilterParamChangedOperation::doOperation() {
	filter->setParam(*param);
}

void FilterParamChangedOperation::undoOperation() {
	filter->restore(memento);
}

}  // namespace operation
}  // namespace controller