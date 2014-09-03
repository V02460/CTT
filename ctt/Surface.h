#ifndef _SURFACE_H
#define _SURFACE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QSize>
#include <QOpenGLFramebufferObject>
#include <QOpenGLTexture>
#include <QOpenGLContext>
#include <QOpenGLShader>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

//#include "GPUSurfaceShader.h"
namespace helper {
    class GPUSurfaceShader;
}

namespace model {

/**
 * Encapsulates an OpenGL texture and a corresponding context.
 * Requires a valid current OpenGL context.
 */
class Surface : protected QOpenGLFunctions {
public:
    typedef QScopedPointer<Surface> uptr;
    typedef QSharedPointer<Surface> sptr;
    typedef QWeakPointer<Surface> wptr;

    /**
     * Creates a new Surface from the submitted context in the given size.
     *
     * @param glContext an OpenGL context, from which the texture is accessible
     * @param size The size of the new Surface
     */
    Surface(QSharedPointer<QOpenGLContext> context, QSize size);

    /**
     * Creates a new Surface from the submitted context in the given size.
     *
     * @param glContext an OpenGL context, from which the texture is accessible
     * @param size The size of the new Surface
     * @param pixelUnpackBufferPtr pointer to GPU owned buffer which is used for texture creation
     * @param pixelType type of pixel data provided in the raw data
     * @param TODO
     */
    Surface(QSharedPointer<QOpenGLContext> context,
            QSize size,
            void **pixelUnpackBufferPtr,
            QOpenGLTexture::PixelType pixelType,
            QOpenGLTexture::PixelFormat pixelFormat,
            QOpenGLTexture::TextureFormat textureFormat);

    /**
     * Returns the size of this surface object.
     *
     * @return QSize The size of the contained image.
     */
    QSize getSize() const;

    /**
     * Gets the underlying OpenGL texture handle.
     * The handle might change over the lifetime of this object.
     *
     * @return GLuint the texture containing the image data of the frame.
     * @throws IllegalStateException if no valid texture handle could be acquired.
     */
    GLuint getTextureHandle() const;

    /**
     * Returns the context in which the texture is accessible.2
     *
     * @return QOpenGLContext a QOpenGLContext in which the texture is accessible
     */
    QSharedPointer<QOpenGLContext> getContext() const;

    /**
     * Returns the share group in which the texture is accessible.
     *
     * @return QOpenGLContextGroup* a QOpenGLContext in which the texture is accessible
     */
    QOpenGLContextGroup *shareGroup() const;

    /**
     * Returns a framebuffer object which can render into this object.
     * Requires an active context from shareGroup().
     * Discards the previous stored texture data.
     *
     * @return QSharedPointer<QOpenGLFramebufferObject> Framebuffer holding the texture of this object
     */
    QOpenGLFramebufferObject *getFramebufferObject();

    /**
     * Returns the stored texture as an byte array.
     * The pixel format is RGBA8888.
     */
    QByteArray getRawRGBA();

    /**
     * Tells the Surface writing to the pixel unpack buffer is completed
     * (only necessary when calling corresponding constructor).
     * The texture will be created and is free to use after this function is called
     */
    void finishTextureUpload();

protected:
    /**
     * Takes over arguments and leaves the old Surface crippled and bleeding on the floor.
     *
     * @param 
     */
    Surface(const Surface &surface);

    /**
     * Get the underlying texture object.
     * May only be called when you can make sure no framebuffer was bound yet.
     *
     * @return QOpenGLTexture* The requested texture object
     */
    QOpenGLTexture *getTexture() const;

private:
    QSharedPointer<QOpenGLContext> context; /**< An OpenGL context, from which the texture is accessible. */
    mutable QScopedPointer<QOpenGLFramebufferObject> framebuffer;
    mutable QScopedPointer<QOpenGLTexture> texture; /**< The OpenGL texture */

    QSize size;

    void initTexture() const;
    void initTexture(QOpenGLTexture::TextureFormat format) const;

    bool isCurrentlyMapped;

    QScopedPointer<QOpenGLBuffer> pixelUnpackBuffer;
    QOpenGLTexture::PixelFormat rawDataPixelFormat;
    QOpenGLTexture::PixelType rawDataPixelType;
    QOpenGLTexture::TextureFormat textureFormat;
};

}  // namespace model

#endif  //_SURFACE_H