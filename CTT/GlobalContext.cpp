#include "GlobalContext.h"

namespace model {
	QScopedPointer<QOpenGLContext> GlobalContext::context;
	QOffscreenSurface GlobalContext::surface;

	QOpenGLContext *GlobalContext::get() {
		if (context.isNull()) {
			context.reset(new QOpenGLContext());
			surface.create();
		}
		context->makeCurrent(&surface);
		return context.data();
	}

}  // namespace model