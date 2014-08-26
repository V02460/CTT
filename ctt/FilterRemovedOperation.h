#ifndef _FILTERREMOVEDOPERATION_H
#define _FILTERREMOVEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"
#include "FilteredVideo.h"

namespace controller {
namespace operation {

/**
* The FilterRemovedOperation is providing functionality for doing and undoing removing a Filter from the FilterList.
**/
class FilterRemovedOperation : public Operation {
public:
    typedef QScopedPointer<FilterRemovedOperation> uptr;
    typedef QSharedPointer<FilterRemovedOperation> sptr;
    typedef QWeakPointer<FilterRemovedOperation> wptr;

    /**
     * Constructs an Operation that is responsible for removing a filter with a specified FilterList-index from this
     * FilterList.
     *
     * @param index The position of the Filter within the FilterList which should be removed from this list.
     * @param filteredVideo The list from which a certain filter should be removed.
     */
    FilterRemovedOperation(int index, ::model::filter::FilteredVideo::sptr filteredVideo);

    /**
     * Manages requests to remove a Filter from a FilterList.
     */
    void doOperation();

    /**
     * Manages requests to undo removing a Filter from a FilterList.
     */
    void undoOperation();

private:
	Q_DISABLE_COPY(FilterRemovedOperation)

	int index;
	::model::filter::FilteredVideo::sptr filteredVideo;
	::model::saveable::Memento memento;
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERREMOVEDOPERATION_H
