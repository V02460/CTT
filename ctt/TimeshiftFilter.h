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

class TimeshiftFilter : public Filter {
public:
	typedef QScopedPointer<TimeshiftFilter> uptr;
	typedef QSharedPointer<TimeshiftFilter> sptr;
	typedef QWeakPointer<TimeshiftFilter> wptr;

	TimeshiftFilter(const Module &predecessor);
	virtual ~TimeshiftFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_TIMESHIFTFILTER_H
