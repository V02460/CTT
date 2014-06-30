#if !defined(_RESCALEFILTER_H)
#define _RESCALEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

class RescaleFilter : public Filter {
public:
	typedef QScopedPointer<RescaleFilter> uptr;
	typedef QSharedPointer<RescaleFilter> sptr;
	typedef QWeakPointer<RescaleFilter> wptr;

	RescaleFilter(const Module &predecessor);
	virtual ~RescaleFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_RESCALEFILTER_H
