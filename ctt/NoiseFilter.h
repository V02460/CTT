#if !defined(_NOISEFILTER_H)
#define _NOISEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

/**
 *	Provides a new version of the predecessors frame where noise has been added.
 */
class NoiseFilter : public Filter {
public:
	typedef QScopedPointer<NoiseFilter> uptr;
	typedef QSharedPointer<NoiseFilter> sptr;
	typedef QWeakPointer<NoiseFilter> wptr;

	/**
	*	Creates a new NoiseFilter object with a given previous module.
	*
	*	@param previous The previous module of this filter.
	*/
	NoiseFilter(Module previous);
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_NOISEFILTER_H
