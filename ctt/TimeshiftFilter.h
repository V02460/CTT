#ifndef _TIMESHIFTFILTER_H
#define _TIMESHIFTFILTER_H

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
 * Provides the unmodified version of a previous or subsequent frame of the predecessor
 */
class TimeshiftFilter : public Filter {
    Q_OBJECT

public:
    typedef QScopedPointer<TimeshiftFilter> uptr;
    typedef QSharedPointer<TimeshiftFilter> sptr;
    typedef QWeakPointer<TimeshiftFilter> wptr;

    static const QByteArray kFilterID;

    static const QString kParamShiftStr;

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
    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("Filter", kFilterID); }
    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
    
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
    static Saveable::sptr getDummy();
    static Saveable::SaveableType getSaveableType() { return Saveable::timeshiftFilter; }

private:
	TimeshiftFilter();
};

}  // namespace filter
}  // namespace model

#endif  //_TIMESHIFTFILTER_H
