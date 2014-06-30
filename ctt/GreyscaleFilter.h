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


/**
 *	Provides a greyscale version of the predecessors frame
 */
class GreyscaleFilter : public Filter {
public:
	typedef QScopedPointer<GreyscaleFilter> uptr;
	typedef QSharedPointer<GreyscaleFilter> sptr;
	typedef QWeakPointer<GreyscaleFilter> wptr;

	/**
	*	Creates a new GreyscaleFilter object with a given previous module
	*
	*	@param previous The previous module of this filter
	*/
	GreyscaleFilter(Module previous);
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_GREYSCALEFILTER_H
