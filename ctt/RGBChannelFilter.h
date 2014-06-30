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

class RGBChannelFilter : public Filter {
public:
	typedef QScopedPointer<RGBChannelFilter> uptr;
	typedef QSharedPointer<RGBChannelFilter> sptr;
	typedef QWeakPointer<RGBChannelFilter> wptr;

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_RGBCHANNELFILTER_H
