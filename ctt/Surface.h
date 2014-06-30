#pragma once
#include "QOpenGLTexture"
#include "QOpenGLContext"

/**
 * Encapsulates a QOpenGLTexture and a corresponding QOpenGLContext.
 */
class Surface
{
public:
	typedef QScopedPointer<Surface> uptr;
	typedef QSharedPointer<Surface> sptr;
	typedef QWeakPointer<Surface> wptr;

	/**
	 * Creates a new Surface from the submitted texture and the submitted context.
	 * WARNING: It can't be ensured that the submitted texture is accessible from the submitted context! If the caller wants an operative Surface, it's up to him to make that sure!
	 * @param glContext an OpenGL context, from which the texture is accessible
	 * @param glTexture the OpenGL texture
	 */
	Surface(QOpenGLContext glContext, QOpenGLTexture glTexture);

	/**
	* Gets the texture containing the image data of the frame.
	*
	* @return QOpenGLTexture the texture containing the image data of the frame.
	*/
	QOpenGLTexture getGLTexture();

	/**
	* Returns a QOpenGLContext in which the texture is accessible.
	* @return QOpenGLContext a QOpenGLContext in which the texture is accessible
	*/
	QOpenGLContext getContext();

protected:
	QOpenGLContext glContext; /**< An OpenGL context, from which the texture is accessible. */
	QOpenGLTexture glTexture; /**< The OpenGL texture */
};

