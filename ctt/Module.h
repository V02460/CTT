#if !defined(_MODULE_H)
#define _MODULE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Saveable.h"
#include "Frame.h"
#include "Memento.h"

namespace model {

/**
 * An object able to provide specific frames from a sequentially numbered set of frames.
 *
 */
class Module : public model::project::Saveable {
public:
    typedef QScopedPointer<Module> uptr;
    typedef QSharedPointer<Module> sptr;
    typedef QWeakPointer<Module> wptr;

    /**
     * Gets the frame with the submitted number.
     *
     * @param frameNumber the number of the frame which shall be returned
     * @return Frame the frame with the submitted number
     * @throws InvalidArgumentException if the submitted frame number is too high.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual model::frame::Frame getFrame(unsigned int frameNumber) = 0;

    /**
     * Gets a list of all Modules this Module uses directly or indirectly to create its frames, including this module
     * itself.
     *
     * @return List<Module> a list of all Modules this Module uses directly or indirectly to create its frames,
     *     including this module itself
     * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual QList<Module> getUsesList() = 0;

    /**
     * Gets the number of the highest frame the module can return.
     *
     * @return int the number of the highest frame the module can return
     * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual unsigned int getFrameCount() const = 0;

    /**
     * Checks whether the submitted module is this module, or used by this module directly or indirectly.
     *
     * @param module it will be checked whether this module is used
     * @return bool true only if the submitted module is this module, or used by this module directly or indirectly
     * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual bool uses(const model::Module &module) const = 0;
};

}  // namespace model

#endif  //_MODULE_H
