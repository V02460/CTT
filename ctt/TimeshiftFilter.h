#if !defined(_TIMESHIFTFILTER_H)
#define _TIMESHIFTFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace filter {

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

/**
 *	Provides the unmodified version of a previous or subsequent frame of the predecessor
 */
class TimeshiftFilter : public Filter {
public:
	typedef QScopedPointer<TimeshiftFilter> uptr;
	typedef QSharedPointer<TimeshiftFilter> sptr;
	typedef QWeakPointer<TimeshiftFilter> wptr;

	/**
	*	Creates a new TimeshiftFilter object with a given previous module.
	*
	*	@param previous The previous module of this filter.
	*/
	TimeshiftFilter(Module previous);
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_TIMESHIFTFILTER_H
