#ifndef _GLOBALCONTEXT_H
#define _GLOBALCONTEXT_H

#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QSharedPointer>

namespace model {

class GlobalContext {

public:
	/**
	 * Returns the OpenGLContext this program is using.
	 */
	static QSharedPointer<QOpenGLContext> get();

private:
	Q_DISABLE_COPY(GlobalContext)

	static QSharedPointer<QOpenGLContext> context;
	static QOffscreenSurface surface;
};

}  // namespace model

#endif  //_GLOBALCONTEXT_H