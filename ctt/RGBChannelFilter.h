#ifndef _RGBCHANNELFILTER_H
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
 * Provides a new version of the predecessors frame where one or more RGB channels have been removed.
 */
class RGBChannelFilter : public Filter {
public:
    typedef QScopedPointer<RGBChannelFilter> uptr;
    typedef QSharedPointer<RGBChannelFilter> sptr;
    typedef QWeakPointer<RGBChannelFilter> wptr;

    /**
    * Creates a new RGBChannelFilter object with a given previous module.
    *
    * @param predecessor The previous module of this filter.
    */
    explicit RGBChannelFilter(Module::sptr predecessor);

    /**
     * RGBChannelFilter destructor.
     */
    virtual ~RGBChannelFilter();
    
    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }

    virtual QString getName() const Q_DECL_OVERRIDE;
    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
	virtual ::model::saveable::Saveable::SaveableType getType() const;

};

}  // namespace filter
}  // namespace model

#endif  //_RGBCHANNELFILTER_H
