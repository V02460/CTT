#if !defined(_FILTERADDEDOPERATION_H)
#define _FILTERADDEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "FilterListOperation.h"
#include "Filter.h"
#include "FilterList.h"

namespace controller {
namespace operation {

/**
*	The FilterAddedOperation is providing the functionality for doing and undoing adding a filter.
**/
class FilterAddedOperation : public FilterListOperation {
public:
	typedef QScopedPointer<FilterAddedOperation> uptr;
	typedef QSharedPointer<FilterAddedOperation> sptr;
	typedef QWeakPointer<FilterAddedOperation> wptr;

	
	/**
	*	Constructs an operation that is responsible for adding a Filter to a video's FilterList.
	*	@param filter The Filter which is to be added.
	*	@param filterList The FilterList the Filter is to be added to.
	**/
	void FilterAddedOperation(Filter filter, FilterList filterList);

	/**
	*	Manages requests to add a Filter to the FilterList.
	**/
	void doOperation();

	/**
	*	Manages requests to undo adding a Filter to the FilterList.
	**/
	void undoOperation();
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERADDEDOPERATION_H
