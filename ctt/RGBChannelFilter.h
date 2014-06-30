#if !defined(_RGBCHANNELFILTER_H)
#define _RGBCHANNELFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

	/**
	 *	Provides a new version of the predecessors frame where one or more RGB channels have been removed.
	 */
class RGBChannelFilter : public Filter {
public:
	typedef QScopedPointer<RGBChannelFilter> uptr;
	typedef QSharedPointer<RGBChannelFilter> sptr;
	typedef QWeakPointer<RGBChannelFilter> wptr;

	/**
	*	Creates a new RGBChannelFilter object with a given previous module.
	*
	*	@param previous The previous module of this filter.
	*/
	RGBChannelFilter(Module previous);
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_RGBCHANNELFILTER_H
