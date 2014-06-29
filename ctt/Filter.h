#if !defined(_FILTER_H)
#define _FILTER_H

#include "Module.h"
#include "Frame.h"
#include "Memento.h"
#include "FilterParam.h"
#include "UIntegerInterval.h"		
#include "FilterIntervalList.h"	
#include <QMap>	

namespace model {
namespace filter {

/**
 * An object which can attach itself to another module and outputs modified versions of the frames of this module.
 *
 */
class Filter : public Module {
public:
    /**
     * Checks whether it is possible to use this Filter not on its previous module as a whole, but only on frames in specific intervals.
     *
     * @return bool true only if the Filter supports being active only in specific intervals.
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual bool supportsIntervals();
    /**
     * Returns a map of the different parameters of the filter with their names and values.
     *
     * @return Map<QString, FilterParam> a map of the different parameters of the filter
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    QMap<QString, FilterParam> getParams();
    /**
     * Tells the Filter to use the frames of the submitted Module as source material for its own frames.
     *
     * @param previous the Filter will use the frames of this module as source material for its own frames
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    void setPreviousModule(Module previous);
    /**
     * Returns a designation of this type of Filter
     *
     * @return QString a designation of this type of Filter
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual QString getName();

	/**
	 * Activates the Filter in the submitted interval.
	 * @param interval the filter will be activated in this interval
	 * @throws IllegalStateException if the the method was called on a dummy or a Filter without interval support
	 */
	void activate(UIntegerInterval interval);

	/**
	 * Deactivates the Filter in the submitted interval.
	 * @param interval the filter will be deactivated in this interval
	 * @throws IllegalStateException if the the method was called on a dummy or a Filter without interval support
	 */
	void deactivate(UIntegerInterval interval);

	/**
	 * Returns a list of all the intervals the filter is active in.
	 * @return List<IntegerInterval> a list of all the intervals the filter is active in
	 * @throws IllegalStateException if the the method was called on a dummy or a Filter without interval support
	 */
	QList<UIntegerInterval> getListOfActiveIntervals();

    virtual Frame getFrame(unsigned int frameNumber);

    virtual Memento getMemento();

    virtual void restore(Memento memento);

private:
    QMap<QString, FilterParam> parameters; /**< Parameters modifying the filters behaviour */
	FilterIntervalList intervals; /**< The Intervals in which the Filtr is active/
    Module *previous; /**< The Filter gets the frames it modifies from this module */
};

}  // namespace filter
}  // namespace model

#endif  //_FILTER_H
