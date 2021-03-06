#ifndef _RGBCHANNELFILTER_H
#define _RGBCHANNELFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QCoreApplication>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

/**
 * Provides a new version of the predecessors frame where one or more RGB channels have been removed.
 */
class RGBChannelFilter : public Filter {
    Q_OBJECT

public:
    typedef QScopedPointer<RGBChannelFilter> uptr;
    typedef QSharedPointer<RGBChannelFilter> sptr;
    typedef QWeakPointer<RGBChannelFilter> wptr;

    static const QByteArray kFilterID;

    static const QByteArray kParamRedStr;
    static const QByteArray kParamGreenStr;
    static const QByteArray kParamBlueStr;

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

    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("Filter", kFilterID); }
    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
	
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
    static Saveable::sptr getDummy();
	static Saveable::SaveableType getSaveableType() { return Saveable::rGBChannelFilter; }
	virtual SaveableType saveableType() const Q_DECL_OVERRIDE { return getSaveableType(); }

private:
	RGBChannelFilter();
};

}  // namespace filter
}  // namespace model

#endif  //_RGBCHANNELFILTER_H
