#if !defined(_GREYSCALEFILTER_H)
#define _GREYSCALEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

class GreyscaleFilter : public Filter {
public:
	typedef QScopedPointer<GreyscaleFilter> uptr;
	typedef QSharedPointer<GreyscaleFilter> sptr;
	typedef QWeakPointer<GreyscaleFilter> wptr;

	GreyscaleFilter(const Module &predecessor);
	virtual ~GreyscaleFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_GREYSCALEFILTER_H
