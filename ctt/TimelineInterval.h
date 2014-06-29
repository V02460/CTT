#if !defined(_TIMELINEINTERVAL_H)
#define _TIMELINEINTERVAL_H

namespace view {

#include "UIntegerInterval.h"

/**
 *	The TimelineInterval is the visual representation of a UIntegerInterval.
 *	It is to visualize the filter intervals and to provide an interactable component for adjusting the interval.
 */
class TimelineInterval{
public:
	/**
	 *	Creates a new TimelineInterval from a concrete filter interval.
	 *
	 *	@param filterInterval The filter interval of its data the TimelineInterval creates itself.
	 */
	TimelineInterval(UIntegerInterval filterInterval);
private:
	UIntegerInterval filterInterval; /**< The corresponding filter interval from the model */
};

}  // namespace view

#endif  //_TIMELINEINTERVAL_H
