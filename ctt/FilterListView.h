#if !defined(_FILTERLISTVIEW_H)
#define _FILTERLISTVIEW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AbstractListView.h"
#include "Filter.h"
#include "FilterParam.h"

namespace view {

/**
 * The FilterListView displays the list of filters in a filtered video.
 * For each filter all of its parameters are shown in a table-like view.
 * For each parameter type (String, int, bool, ...) there is a specific component (spinbox, textarea, ...) so that those
 * parameters can be easily changed by just clicking on them and adjusting its value.
 */
class FilterListView : public AbstractListView {
public:
    typedef QScopedPointer<FilterListView> uptr;
    typedef QSharedPointer<FilterListView> sptr;
    typedef QWeakPointer<FilterListView> wptr;

signals:
    /**
     * This signal is emitted when the order of the filters is changed
     * so when the filter is moved from its old position to a new position.
     *
     * @param oldPos The old position of the filter.
     * @param newPos The new/desired position of the filter.
     */
    void filterMoved(int oldPos, int newPos);

    /**
     * This signal is emitted when any filter parameter is changed by the user.
     *    
     * @param filter The filter of which the parameter has changed.
     * @param param The parameter that has changed with its new value.
     */
    void filterParamChanged(const ::model::filter::Filter &filter, const ::model::filter::FilterParam &param);
};

}  // namespace view

#endif  //_FILTERLISTVIEW_H
