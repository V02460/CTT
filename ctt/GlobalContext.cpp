#include "GlobalContext.h"

namespace model {

GlobalContext::GlobalContext() : context(new QOpenGLContext()), offscreenSurface() {
    offscreenSurface.create();
}

}  // namespace model