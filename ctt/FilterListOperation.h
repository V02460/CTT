#if !defined(_FILTERLISTOPERATION_H)
#define _FILTERLISTOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"
#include "Filter.h"
#include "FilteredVideo.h"

namespace controller {
namespace operation {

/**
 * The FilterListOperation is providing functionality for doing and undoing manipulations of the FilterList.
 */
class FilterListOperation : public Operation {
public:
    typedef QScopedPointer<FilterListOperation> uptr;
    typedef QSharedPointer<FilterListOperation> sptr;
    typedef QWeakPointer<FilterListOperation> wptr;

    /**
     * Manages requests to manipulate the FilterList.
     */
    void doOperation();

    /**
     * Manages requests to undo manipulations of the FilterList.
     */
    void undoOperation();

protected:
    ::model::filter::Filter filter;
    int index;
    ::model::filter::FilteredVideo filteredVideo;
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERLISTOPERATION_H
