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

	/**
	 *	Provides a new version of the predecessors frame which has been rescaled.
	 */
class RescaleFilter : public Filter {
public:
	typedef QScopedPointer<RescaleFilter> uptr;
	typedef QSharedPointer<RescaleFilter> sptr;
	typedef QWeakPointer<RescaleFilter> wptr;

	/**
	*	Creates a new RescaleFilter object with a given previous module.
	*
	*	@param previous The previous module of this filter.
	*/
	RescaleFilter(Module previous);
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_RESCALEFILTER_H
