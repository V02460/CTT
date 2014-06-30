#if !defined(_BLURFILTER_H)
#define _BLURFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"
#include "Saveable.h"

namespace model {
namespace filter {

/**
 *	Provides a blured version of the predecessors frame.
 */
class BlurFilter : public Filter {
public:
	typedef QScopedPointer<BlurFilter> uptr;
	typedef QSharedPointer<BlurFilter> sptr;
	typedef QWeakPointer<BlurFilter> wptr;

	/**
	 *	Creates a new BlurFilter object with a given previous module.
	 *
	 *	@param previous The previous module of this filter.
	 */
	BlurFilter(Module previous);
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_BLURFILTER_H
