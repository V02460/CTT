#ifndef _RESCALEFILTER_H
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
* Provides a new version of the predecessors frame which has been rescaled.
*/
class RescaleFilter : public Filter {
public:
    typedef QScopedPointer<RescaleFilter> uptr;
    typedef QSharedPointer<RescaleFilter> sptr;
    typedef QWeakPointer<RescaleFilter> wptr;

    /**
     * Creates a new RescaleFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit RescaleFilter(Module::sptr predecessor);

    /**
     * Destroys the RescaleFilter.
     */
    virtual ~RescaleFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return false; }
    virtual QString getName() const;
	virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
	
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const ::model::Module*> getUsesList() const Q_DECL_OVERRIDE;
    static Saveable::SaveableType getSaveableType();
};

}  // namespace filter
}  // namespace model

#endif  //_RESCALEFILTER_H
