#if !defined(_MIXFILTER_H)
#define _MIXFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

class MixFilter : public Filter {
public:
	typedef QScopedPointer<MixFilter> uptr;
	typedef QSharedPointer<MixFilter> sptr;
	typedef QWeakPointer<MixFilter> wptr;

	MixFilter(const Module &predecessor);
	virtual ~MixFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_MIXFILTER_H
