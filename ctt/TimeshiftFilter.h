#ifndef _TIMESHIFTFILTER_H
#define _TIMESHIFTFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

/**
 * Provides the unmodified version of a previous or subsequent frame of the predecessor
 */
class TimeshiftFilter : public Filter {
public:
    typedef QScopedPointer<TimeshiftFilter> uptr;
    typedef QSharedPointer<TimeshiftFilter> sptr;
    typedef QWeakPointer<TimeshiftFilter> wptr;

    /**
     * Creates a new TimeshiftFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit TimeshiftFilter(Module::sptr predecessor);

    /**
     * Destroys the TimeshiftFilter.
     */
    virtual ~TimeshiftFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const Q_DECL_OVERRIDE { return "filter_timeshift"; }
    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
    
    virtual ::model::saveable::Saveable::SaveableType getType() const Q_DECL_OVERRIDE { return Saveable::timeshiftFilter };
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const ::model::Module*> getUsesList() const Q_DECL_OVERRIDE;
    virtual bool uses(const ::model::Module &module) const Q_DECL_OVERRIDE;
    static Saveable::sptr getDummy();

private:
    static const QString kParamShiftStr;
};

}  // namespace filter
}  // namespace model

#endif  //_TIMESHIFTFILTER_H
