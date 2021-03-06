#ifndef _FILTERINTERVALLIST_H
#define _FILTERINTERVALLIST_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QObject>

#include "UIntegerInterval.h"
#include "Saveable.h"
#include "Memento.h"

namespace model {

/**
 * Manages a list of intervals in which a something is active.
 *
 */
class FilterIntervalList : public ::model::saveable::Saveable {
public:
    typedef QScopedPointer<FilterIntervalList> uptr;
    typedef QSharedPointer<FilterIntervalList> sptr;
    typedef QWeakPointer<FilterIntervalList> wptr;

    /**
    * Creates an empty FilterIntervalList.
    *
    */
    FilterIntervalList();

    /**
     * Checks whether the submitted number is in an active interval.
     *
     * @param frameNumber it is checked whether this number is in an active interval
     * @return bool true only if the submitted number is in an active interval
     * @throws IllegalStateException if the the method was called on a dummy
     */
    bool isActive(unsigned int frameNumber) const;

    /**
     * Makes the submitted Interval an active Interval. If possible, it will be merged with existing active Intervals.
     *
     * @param interval this Interval is made an active interval.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void activate(UIntegerInterval::sptr interval);

    /**
     * Makes the submitted Interval an inactive Interval.
     *
     * @param interval this Interval is made an inactive interval.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void deactivate(UIntegerInterval::sptr interval);

    /**
     * Returns a list of all the active Intervals.
     *
     * @return List<IntegerInterval> a list of all the active Intervals
     * @throws IllegalStateException if the the method was called on a dummy
     */
    QList<UIntegerInterval::sptr> getIntervalList() const;

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    static Saveable::sptr getDummy();
	static Saveable::SaveableType getSaveableType();
	virtual SaveableType saveableType() const Q_DECL_OVERRIDE { return getSaveableType(); }

private:
    QList<UIntegerInterval::sptr> intervals;
};

}  // namespace model

#endif  //_FILTERINTERVALLIST_H