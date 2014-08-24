#ifndef _GLOBALCONTEXT_H
#define _GLOBALCONTEXT_H

#include <QOffscreenSurface>
#include <QOpenGLContext>

namespace model {

class GlobalContext {

public:
	/**
	 * Returns the OpenGLContext this program is using.
	 */
	static QOpenGLContext *get();

private:
	Q_DISABLE_COPY(GlobalContext)

	GlobalContext();

	static GlobalContext *getInstance();

	static QScopedPointer<GlobalContext> instance;

	QScopedPointer<QOpenGLContext> context;
	mutable QOffscreenSurface offscreenSurface;
};

}  // namespace model

#endif  //_GLOBALCONTEXT_H