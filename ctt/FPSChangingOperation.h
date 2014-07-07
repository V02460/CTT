#ifndef _FPSCHANGINGOPERATION_H
#define _FPSCHANGINGOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"

namespace controller {
namespace operation {

/**
 * The FPSChangingOperation is providing functionality for doing and undoing changing the FPS with which a video is
 * displayed.
 */
class FPSChangingOperation : public Operation {
public:
    typedef QScopedPointer<FPSChangingOperation> uptr;
    typedef QSharedPointer<FPSChangingOperation> sptr;
    typedef QWeakPointer<FPSChangingOperation> wptr;

    /**
     * Constructs an Operation that is responsible for changing the FPS with which a video is displayed.
     *
     * @param fps The FPS with which a video is displayed.
     */
    FPSChangingOperation(double fps);

    /**
     * Manages requests to change the FPS with which a video is displayed.
     */
    void doOperation();

    /**
     * Manages requests to undo changing the FPS with which a video is displayed.
     */
    void undoOperation();
private:
    double oldFPS;
    double newFPS;
};

}  // namespace operation
}  // namespace controller

#endif  //_FPSCHANGINGOPERATION_H
