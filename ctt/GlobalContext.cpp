#include "GlobalContext.h"

namespace model {

QSharedPointer<QOpenGLContext> GlobalContext::get() {
    if (context.isNull()) {
        context.reset(new QOpenGLContext());
        context->create();

        surface.reset(new QOffscreenSurface());
        surface->create();
    }
    context->makeCurrent(surface.data());
    return context;
}

QSharedPointer<QOpenGLContext> GlobalContext::context;
QScopedPointer<QOffscreenSurface> GlobalContext::surface;

}  // namespace model