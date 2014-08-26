#ifndef _FILTERMOVEDOPERATION_H
#define _FILTERMOVEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"
#include "FilteredVideo.h"
#include "Filter.h"

namespace controller {
namespace operation {

/**
 * The FilterMovedOperation is providing functionality for doing and undoing changing a Filter's position.
 */
class FilterMovedOperation : public Operation {
public:
	typedef QScopedPointer<FilterMovedOperation> uptr;
	typedef QSharedPointer<FilterMovedOperation> sptr;
	typedef QWeakPointer<FilterMovedOperation> wptr;

    /**
     * Constructs an Operation that is responsible for changing the position of a filter in a filtered video.
	 *
	 * @param oldPos The old position of the filter in the old list.
	 * @param newPos The new position of the filter in the old list.
	 * @param filtrerdVideo The filtered video to apply the change to.
     */
	FilterMovedOperation(int oldPos, int newPos, model::filter::FilteredVideo::sptr filteredVideo);

    /**
     * Manages requests to change a filter's position.
     */
    void doOperation();

    /**
     * Manages requests undo changing a filter's position.
     */
    void undoOperation();

private:
	Q_DISABLE_COPY(FilterMovedOperation)

	int oldPos;
	int newPos; // The new position of the filter in the new(!) list.
	model::filter::FilteredVideo::sptr filteredVideo;
	::model::saveable::Memento memento;
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERMOVEDOPERATION_H
