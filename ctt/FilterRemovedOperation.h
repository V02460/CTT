#if !defined(_FILTERREMOVEDOPERATION_H)
#define _FILTERREMOVEDOPERATION_H

#include "FilterListOperation.h"
#include "FilterList.h"

namespace controller {
namespace operation {

/**
*	The FilterRemovedOperation is providing functionality for doing and undoing removing a Filter from the FilterList.
**/
class FilterRemovedOperation : public FilterListOperation {
public:

	/**
	*	Constructs an Operation that is responsible for removing a filter with a specified FilterList-index from this FilterList.
	*	@param index The position of the Filter within the FilterList which should be removed from this list.
	*	@param filterList The list from which a certain filter should be removed.
	**/
	FilterRemovedOperation(int index, FilterList filterList);

	/**
	*	Manages requests to remove a Filter from a FilterList.
	**/
	void doOperation();

	/**
	*	Manages requests to undo removing a Filter from a FilterList.
	**/
	void undoOperation();
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERREMOVEDOPERATION_H
