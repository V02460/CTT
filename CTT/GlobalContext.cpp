#include "GlobalContext.h"

#include "OpenGLException.h"

namespace model {

using ::exception::OpenGLException;

QSharedPointer<QOpenGLContext> GlobalContext::get() {
    if (context.isNull()) {
        context.reset(new QOpenGLContext());
        if (!context->create()) {
            throw OpenGLException("Could not create default context.");
        }

        surface.reset(new QOffscreenSurface());
        surface->create();
        if (!surface->isValid()) {
            throw OpenGLException("Could not allocate offscreen surface.");
        }
    }

    if (!context->makeCurrent(surface.data())) {
        throw OpenGLException("Could not make the default context the current context.");
    }

    return context;
}

QSharedPointer<QOpenGLContext> GlobalContext::context;
QScopedPointer<QOffscreenSurface> GlobalContext::surface;

}  // namespace model