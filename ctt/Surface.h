#ifndef _SURFACE_H
#define _SURFACE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "QOpenGLTexture"
#include "QOpenGLContext"

namespace model {

/**
 * Encapsulates a QOpenGLTexture and a corresponding QOpenGLContext.
 * Requires a valid current OpenGL context.
 */
class Surface
{
public:
	typedef QScopedPointer<Surface> uptr;
	typedef QSharedPointer<Surface> sptr;
	typedef QWeakPointer<Surface> wptr;

	/**
	 * Creates a new Surface from the submitted texture and the submitted context.
     *
	 * @param glContext an OpenGL context, from which the texture is accessible
	 * @param glTexture the OpenGL texture
	 */
    Surface(QSharedPointer<QOpenGLContext> glContext, QSize size);

	/**
	* Gets the texture containing the image data of the frame.
	*
	* @return QOpenGLTexture the texture containing the image data of the frame.
	*/
    const QOpenGLTexture &getGLTexture() const;

	/**
	* Returns a QOpenGLContext in which the texture is accessible.
	* @return QOpenGLContext a QOpenGLContext in which the texture is accessible
	*/
    QSharedPointer<QOpenGLContext> getContext();

protected:
    QSharedPointer<QOpenGLContext> glContext; /**< An OpenGL context, from which the texture is accessible. */
    QOpenGLTexture glTexture; /**< The OpenGL texture */
};

}  // namespace model

#endif  //_SURFACE_H