#ifndef _FRAMEDIFF_H
#define _FRAMEDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Saveable.h"
#include "Module.h"
#include "Memento.h"

namespace model {
namespace difference {

/**
 * A FrameDiff compares corresponding frames from two specific videos and calculates one-dimensional distances between them.
 */
class FrameDiff : public ::model::saveable::Saveable, public ::model::Observer, public ::model::Observable {
public:
    typedef QScopedPointer<FrameDiff> uptr;
    typedef QSharedPointer<FrameDiff> sptr;
    typedef QWeakPointer<FrameDiff> wptr;

    /**
     * Calculates and returns a value between 0 and 1 to indicate the difference between the frames with the
	 * submitted number of the two videos this FrameDiff compares. A low value means the frames were similar,
	 * a value close to 1 indicates a huge difference.
     *
     * @param frameNr the frames with this number will be compared
     * @return double the calculated distance between the two frames
     * @throws IllegalArgumentException if one or both of the videos don't have a frame with the submitted number
     */
    virtual double getDiff(unsigned int frameNr) = 0;

    /**
     * Returns the number of frames the shorter Video has, i.e. the number of frames the FrameDiff can calculate a
     * difference to.
     *
     * @return unsigned int the number of frames the shorter Video has
     */
    unsigned int getFrameCount() const;

    /**
     * Returns the name of the FrameDiff.
     *
     * @return the name of the FrameDiff
     */
    virtual QString getName() const = 0;

    /**
     * Returns the first Module of the FrameDiff.
     *
     * @return the first Module
     */
    ::model::Module::sptr getModule1();

    /**
     * Returns the second Module of the FrameDiff.
     *
     * @return the second Module
     */
    ::model::Module::sptr getModule2();

	virtual void update() Q_DECL_OVERRIDE;

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    static Saveable::SaveableType getSaveableType();

protected:
    /**
    * Constructs the FrameDiff by taking two videos used to calculate their frame difference.
    *
    * @param module1 First video used for comparison
    * @param module2 Second video comparison
    */
    FrameDiff(::model::Module::sptr module1, ::model::Module::sptr module2);

    /**
    * Constructs a dummy FrameDiff.
    */
    FrameDiff::FrameDiff();

    /**
    * FrameDiff Destructor
    */
    virtual ~FrameDiff();

	/** The first of the two Videos which this FrameDiff compares. */
    ::model::Module::sptr module1;
	/** The second of the two Videos which this FrameDiff compares. */
    ::model::Module::sptr module2;

	bool isCalculated;
	QMap<unsigned int, double> diff;

private:
	virtual void calculateFrameDiff(unsigned int frameNr) = 0;
    Q_DISABLE_COPY(FrameDiff)
};

}  // namespace difference
}  // namespace model

#endif  //_FRAMEDIFF_H
