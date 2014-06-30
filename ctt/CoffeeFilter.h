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

	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_COFFEEFILTER_H
