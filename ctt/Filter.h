


#if !defined(_FILTER_H)
#define _FILTER_H

#include "Module.h"
#include "Frame.h"
#include "Memento.h"
#include "FilterParam.h"
#include "IntegerInterval.h"		

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
    virtual Map<QString, FilterParam> getParams();
    /**
     * Tells the Filter to use the frames of the submitted Module as source material for its own frames.
     *
     * @param previous the Filter will use the frames of this module as source material for its own frames
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual void setPreviousModule(Module previous);
    /**
     * Returns a designation of this type of Filter
     *
     * @return QString a designation of this type of Filter
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual QString getName();

    virtual Frame getFrame(unsigned int frameNumber);

    virtual Memento getMemento();

    virtual void restore(Memento memento);

    virtual Saveable* getDummy();
private:
    Map<QString, FilterParam> parameters; /**< Parameters modifying the filters behaviour */
    /**< TODO irgendwas mit den intervallen */
    Module *previous; /**< The Filter gets the frames it modifies from this module */
};

#endif  //_FILTER_H
