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

/**
 *	Provides a new version of the predecessors frame which has been mixed with another texture.
 */
class MixFilter : public Filter {
public:
	typedef QScopedPointer<MixFilter> uptr;
	typedef QSharedPointer<MixFilter> sptr;
	typedef QWeakPointer<MixFilter> wptr;

	/**
	*	Creates a new MixFilter object with a given previous module and a sufrace which provides the texture to be mixed with a frame.
	*
	*	@param previous The previous module of this filter.
	*	@param surface The surface which provides the texture to be mixed with a frame.
	*/
	MixFilter(Module previous, Surface surface)
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_MIXFILTER_H
