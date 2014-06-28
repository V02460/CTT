


#if !defined(_MODULE_H)
#define _MODULE_H

#include "Saveable.h"
#include "Frame.h"
#include "Memento.h"

/**
 * An object able to provide specific frames from a sequentially numbered set of frames.
 *
 */
class Module : public Saveable {
public:
    /**
     * Gets the frame with the submitted number.
     *
     * @param frameNumber the number of the frame which shall be returned
     * @return Frame the frame with the submitted number
     * @throws InvalidArgumentException if the submitted frame number is too high.
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual Frame getFrame(unsigned int frameNumber);

    /**
     * Gets a list of all Modules this Module uses directly or indirectly to create its frames, including this module itself.
     *
     * @return List<Module> a list of all Modules this Module uses directly or indirectly to create its frames, including this module itself
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual List<Module> getUsesList();

    /**
     * Gets the number of the highest frame the module can return.
     *
     * @return int the number of the highest frame the module can return
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual unsigned int getFrameCount();

    /**
     * Checks whether the submitted module is this module, or used by this module directly or indirectly.
     *
     * @param module it will be checked whether this module is used
     * @return bool true only if the submitted module is this module, or used by this module directly or indirectly
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual bool uses(Module module);

    virtual Memento getMemento();

    virtual void restore(Memento memento);

    virtual Saveable* getDummy();
};

#endif  //_MODULE_H
