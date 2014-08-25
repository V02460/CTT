#ifndef _GLOBALCONTEXT_H
#define _GLOBALCONTEXT_H

#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QSharedPointer>
#include <QScopedPointer>

namespace model {

class GlobalContext {

public:
	/**
	 * Returns the OpenGLContext this program is using.
	 */
	static QSharedPointer<QOpenGLContext> get();

private:
	Q_DISABLE_COPY(GlobalContext)

    GlobalContext();
    ~GlobalContext();

	static QSharedPointer<QOpenGLContext> context;
	static QScopedPointer<QOffscreenSurface> surface;
};

}  // namespace model

#endif  //_GLOBALCONTEXT_H