#include "Surface.h"

#include "GPUSurfaceShader.h"
#include "OpenGLException.h"

#include "IllegalStateException.h"
#include "NotImplementedException.h"

namespace model {
    
using ::helper::GPUSurfaceShader;
using ::exception::IllegalStateException;
using ::exception::OpenGLException;
using ::exception::NotImplementedException;

typedef QSharedPointer<QOpenGLContext> QOpenGLContext_sptr;

Surface::Surface(QOpenGLContext_sptr context, QSize size)
        : context(context)
        , size(size)
        , framebuffer(nullptr)
        , isCurrentlyMapped(false)
        , textureFormat(QOpenGLTexture::RGBA8_UNorm) {
}

Surface::Surface(QOpenGLContext_sptr context,
                 QSize size,
                 void **pixelUnpackBufferPtr,
                 QOpenGLTexture::PixelType pixelType,
                 QOpenGLTexture::PixelFormat pixelFormat,
                 QOpenGLTexture::TextureFormat textureFormat)
        : context(context)
        , size(size)
        , framebuffer(nullptr)
        , pixelUnpackBuffer(new QOpenGLBuffer(QOpenGLBuffer::PixelUnpackBuffer))
        , isCurrentlyMapped(true)
        , rawDataPixelType(pixelType)
        , rawDataPixelFormat(pixelFormat)
        , textureFormat(textureFormat) {

    if (pixelType != QOpenGLTexture::UInt8) {
        throw NotImplementedException("Only pixel type UInt8 is currently supported.");
    }
    if (!pixelUnpackBuffer->create()) {
        throw OpenGLException("Could not create pixel unpack buffer.");
    }
    if (pixelUnpackBuffer->bind()) {
        throw OpenGLException("Could not bind pixel unpack buffer.");
    }

    // TODO: change for arbitrary pixel types
    pixelUnpackBuffer->allocate(size.width() * size.height());

    *pixelUnpackBufferPtr = pixelUnpackBuffer->map(QOpenGLBuffer::WriteOnly);
    if (*pixelUnpackBufferPtr == nullptr) {
        throw OpenGLException("Could not map pixel unpack buffer to client memory.");
    }

    pixelUnpackBuffer->release();
}

void Surface::finishTextureUpload() {
    if (!isCurrentlyMapped) {
        throw new IllegalStateException("No texture upload in progress. Call to this function is not needed.");
    }

    if (pixelUnpackBuffer->unmap()) {
        throw OpenGLException("Unmapping of pixel unpack buffer failed.");
    }

    isCurrentlyMapped = false;

    initTexture(textureFormat);

    pixelUnpackBuffer->bind();
    texture->setData(rawDataPixelFormat, rawDataPixelType, static_cast<void*>(0));

    pixelUnpackBuffer->release();
}

QSize Surface::getSize() const {
    return size;
}

GLuint Surface::getTextureHandle() const {
    if (isCurrentlyMapped) {
        throw new IllegalStateException("Pixel unpack buffer is currently mapped. Call finishTextureUpload() first.");
    }

    GLuint handle = 0;

    if (framebuffer) {
        handle = framebuffer->texture();
        if (handle == 0) {
            throw IllegalStateException("Framebuffer object returned an invalid handle.");
        }
    } else {
        if (!texture) {
            initTexture();
        }

        handle = texture->textureId();
        if (handle == 0) {
            throw IllegalStateException("Texture object returned an invalid handle.");
        }
    }

    return handle;
}

QSharedPointer<QOpenGLContext> Surface::getContext() const {
    return context;
}

QOpenGLContextGroup *Surface::shareGroup() const {
    return context->shareGroup();
}

QOpenGLFramebufferObject *Surface::getFramebufferObject() {
    if (!framebuffer) {
        framebuffer.reset(new QOpenGLFramebufferObject(size));

        if (!framebuffer->isValid()) {
            throw OpenGLException("Framebuffer initialization failed. Size was "
                                    + QString::number(size.width())
                                    + "x"
                                    + QString::number(size.height())
                                    + ".");
        }

        // don't store two textures
        texture.reset();
    }

    return framebuffer.data();
}

// TODO: make const
QByteArray Surface::getRawRGBA() {
    //TODO: find nicer way to handle changing contexts
    initializeOpenGLFunctions();

    QByteArray data;
    data.resize(4 * size.width() * size.height());

    glBindTexture(GL_TEXTURE_2D, getTextureHandle());

    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    //glReadPixels(0, 0, size.width(), size.height(), GL_RGBA, GL_UNSIGNED_BYTE, data.data());

    glBindTexture(GL_TEXTURE_2D, 0);

    return data;
}

Surface::Surface(const Surface &surface)
        : context(surface.context)
        , framebuffer(surface.framebuffer.take())
        , texture(surface.texture.take())
        , size(surface.size) {
}

QOpenGLTexture *Surface::getTexture() const {
    if (framebuffer) {
        throw IllegalStateException("Surface has a framebuffer: Don't request texture.");
    }

    if (!texture) {
        initTexture();
    }

    return texture.data();
}

void Surface::initTexture(QOpenGLTexture::TextureFormat format) const {
    if (texture) { // already initialized
        return;
    }

    texture.reset(new QOpenGLTexture(QOpenGLTexture::Target2D));
    texture->setSize(size.width(), size.height());
}

void Surface::initTexture() const {
    return initTexture(QOpenGLTexture::RGBA8_UNorm);
}

}  // namespace model