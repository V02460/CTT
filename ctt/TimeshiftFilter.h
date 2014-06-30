#if !defined(_TIMESHIFTFILTER_H)
#define _TIMESHIFTFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

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
	*	@param predecessor The previous module of this filter.
	*/
	TimeshiftFilter(const Module &predecessor);
	virtual ~TimeshiftFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_TIMESHIFTFILTER_H
