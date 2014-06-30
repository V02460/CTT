#if !defined(_COFFEEFILTER_H)
#define _COFFEEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

class CoffeeFilter : public Filter {
public:
	typedef QScopedPointer<CoffeeFilter> uptr;
	typedef QSharedPointer<CoffeeFilter> sptr;
	typedef QWeakPointer<CoffeeFilter> wptr;

	CoffeeFilter(const Module &predecessor);
	virtual ~CoffeeFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_COFFEEFILTER_H
