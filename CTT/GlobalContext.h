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

			static QScopedPointer<QOpenGLContext> context;
		static QOffscreenSurface surface;
	};

}  // namespace model

#endif  //_GLOBALCONTEXT_H