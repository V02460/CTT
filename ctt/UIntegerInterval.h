#if !defined(_UINTEGERINTERVAL_H)
#define _UINTEGERINTERVAL_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Saveable.h"

namespace model {

/**
 * Represents an interval of integers, defined by a start and end point.
 *
 */
class UIntegerInterval: public ::model::project::Saveable {
public:
    typedef QScopedPointer<UIntegerInterval> uptr;
    typedef QSharedPointer<UIntegerInterval> sptr;
    typedef QWeakPointer<UIntegerInterval> wptr;

    /**
     * Creates an IntegerInterval from a to b if b isn't smaller than a, else it creates an Interval from b to a.
     *
     * @param a one of the end points of the interval.
     * @param a one of the end points of the interval.
     */
    UIntegerInterval(unsigned int a, unsigned int b);

    /**
     * Checks whether x is an element of the interval.
     *
     * @param x for this value will be checked whether it is an element of the interval
     * @return bool true only if x is an element of the interval
     */
    bool contains(unsigned int x) const;

    /**
     * Returns the smallest element of the interval.
     *
     * @return int the smallest element of the interval
     */
    int getStart() const;

    /**
     * Returns the greatest element of the interval.
     *
     * @return int the greatest element of the interval
     */
    int getEnd() const;

    /**
     * Moves the lower bound of the interval to start.
     *
     * @param start the lower bound of the interval will be moved to this value.
     * @throws IllegalArgumentException if start is greater than the current upper bound of the interval
     */
    void setStart(unsigned int start);

    /**
    * Moves the upper bound of the interval to end.
    *
    * @param end the upper bound of the interval will be moved to this value.
    * @throws IllegalArgumentException if end is smaller than the current lower bound of the interval
    */
    void setEnd(unsigned int end);

    /**
     * Checks whether this interval has an intersection with the submitted interval which isn't empty, i.e. whether the
     * union of the intervals is an interval.
     *
     * @param interval it will be checked whether merging is possible with this interval
     * @return bool true only if the union of the intervals is an interval
     */
    bool canMergeWith(UIntegerInterval interval) const;

    /**
     * Makes this interval a union of itself and the submitted interval. This only works if the union is an interval
     * itself.
     *
     * @param interval the interval will be merged with this interval
     * @throws IllegalArgumentException if the the interception between this interval and the submitted interval is
     *     empty
     */
    void mergeWith(UIntegerInterval interval) const;

    virtual ::model::project::Memento getMemento() const;
    virtual void restore(::model::project::Memento memento);
    static Saveable::sptr getDummy();

private:
    /**
    * Creates a dummy IntegerInterval.
    */
    UIntegerInterval();

    unsigned int start; /**< The lower bound of the interval */
    unsigned int end; /**< The upper bound of the interval */
};

}  // namespace model

#endif  //_UINTEGERINTERVAL_H
