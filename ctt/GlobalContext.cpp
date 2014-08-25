#include "GlobalContext.h"

namespace model {

QSharedPointer<QOpenGLContext> GlobalContext::get() {
    if (context.isNull()) {
        context.reset(new QOpenGLContext());
        surface.create();
    }
    context->makeCurrent(&surface);
    return context;
}

QSharedPointer<QOpenGLContext> GlobalContext::context(new QOpenGLContext());
QOffscreenSurface GlobalContext::surface;

}  // namespace model