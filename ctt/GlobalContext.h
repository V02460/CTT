#ifndef _GLOBALCONTEXT_H
#define _GLOBALCONTEXT_H

#include <QOffscreenSurface>

namespace model {

class GlobalContext {
public:
	static QOpenGLContext *get();

private:
	GlobalContext();

	GlobalContext *getInstance();

	static QScopedPointer<GlobalContext> instance;

	QScopedPointer<QOpenGLContext> context;
	mutable QOffscreenSurface offscreenSurface;
};

}  // namespace model

#endif  //_GLOBALCONTEXT_H