#ifndef _TIMELINEINTERVAL_H
#define _TIMELINEINTERVAL_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "UIntegerInterval.h"

namespace view {

/**
 * The TimelineInterval is the visual representation of a UIntegerInterval.
 * It is to visualize the filter intervals and to provide an interactable component for adjusting the interval.
 */
class TimelineInterval{
public:
    typedef QScopedPointer<TimelineInterval> uptr;
    typedef QSharedPointer<TimelineInterval> sptr;
    typedef QWeakPointer<TimelineInterval> wptr;

    /**
     * Creates a new TimelineInterval from a concrete filter interval.
     *
     * @param filterInterval The filter interval of its data the TimelineInterval creates itself.
     */
    TimelineInterval(::model::UIntegerInterval filterInterval);
private:
    ::model::UIntegerInterval::sptr filterInterval; /**< The corresponding filter interval from the model */
};

}  // namespace view

#endif  //_TIMELINEINTERVAL_H
