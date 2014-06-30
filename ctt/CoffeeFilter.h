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

/**
 *	Provides a version of the predecessors frame with coffee stains on it.
 */
class CoffeeFilter : public Filter {
public:
	typedef QScopedPointer<CoffeeFilter> uptr;
	typedef QSharedPointer<CoffeeFilter> sptr;
	typedef QWeakPointer<CoffeeFilter> wptr;

	/**
	*	Creates a new CoffeeFilter object with a given previous module.
	*
	*	@param predecessor The previous module of this filter.
	*/
	CoffeeFilter(const Module &predecessor);
	virtual ~CoffeeFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_COFFEEFILTER_H
