#if !defined(_BLURFILTER_H)
#define _BLURFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

class BlurFilter : public Filter {
public:
	typedef QScopedPointer<BlurFilter> uptr;
	typedef QSharedPointer<BlurFilter> sptr;
	typedef QWeakPointer<BlurFilter> wptr;

	BlurFilter(const Module &predecessor);
	virtual ~BlurFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_BLURFILTER_H
