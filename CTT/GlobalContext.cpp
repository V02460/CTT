#include "GlobalContext.h"

namespace model {

GlobalContext::GlobalContext() : context(new QOpenGLContext()), offscreenSurface() {
    offscreenSurface.create();
}

QOpenGLContext *GlobalContext::get() {
	GlobalContext *gc = getInstance();
	QOpenGLContext *openGLContext = gc->context.data();
	openGLContext->makeCurrent(&gc->offscreenSurface);
	return openGLContext;
}

GlobalContext *GlobalContext::getInstance() {
	if (instance.isNull()) {
		instance.reset(new GlobalContext());
	}
	return instance.data();
}

QScopedPointer<GlobalContext> GlobalContext::instance = QScopedPointer<GlobalContext>(new QOpenGLContext);

}  // namespace model