#include "GlobalContext.h"

namespace model {

QOpenGLContext *GlobalContext::get() {
    if (context.isNull()) {
        context.reset(new QOpenGLContext());
        surface.create();
    }
    context->makeCurrent(&surface);
    return context.data();
}

}  // namespace model