#if !defined(_FILTERLISTOPERATION_H)
#define _FILTERLISTOPERATION_H

#include "Operation.h"
#include "Filter.h"
#include "FilterList.h"

namespace controller {
namespace operation {

/**
*	The FilterListOperation is providing functionality for doing and undoing manipulations of the FilterList.
**/
class FilterListOperation : public Operation {
public:

	/**
	*	Manages requests to manipulate the FilterList.
	**/
	void doOperation();

	/**
	*	Manages requests to undo manipulations of the FilterList.
	**/
	void undoOperation();
protected:
	Filter filter;
	int index;
	FilterList filterList;
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERLISTOPERATION_H
