#pragma once
#include "QOpenGLTexture"
#include "QOpenGLContext"

/**
 * Encapsulates a QOpenGLTexture and a corresponding QOpenGLContext.
 */
class Surface
{
public:

	Surface();

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

