#include "Surface.h"

#include "GPUHelper.h"

#include "IllegalStateException.h"

namespace model {
    
using ::helper::GPUHelper;
using ::exception::IllegalStateException;

typedef QSharedPointer<QOpenGLContext> QOpenGLContext_sptr;

Surface::Surface(QOpenGLContext_sptr context, QSize size) : context(context), size(size), framebuffer(nullptr) {
}

QSize Surface::getSize() const {
    return size;
}

GLuint Surface::getTextureHandle() const {
    GLuint handle = 0;

    if (framebuffer) {
        handle = framebuffer->texture();
        if (handle == 0) {
            throw new IllegalStateException("Framebuffer object returned an invalid handle.");
        }
    } else {
        if (!texture) {
            initTexture();
        }

        handle = texture->textureId();
        if (handle == 0) {
            throw new IllegalStateException("Texture object returned an invalid handle.");
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

        // don't store two textures
        texture.reset();
    }

    return framebuffer.data();
}

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
        throw new IllegalStateException("Surface has a framebuffer: Don't request texture.");
    }

    if (!texture) {
        initTexture();
    }

    return texture.data();
}

void Surface::initTexture() const {
    if (texture) { // already initialized
        return;
    }

    texture.reset(new QOpenGLTexture(QOpenGLTexture::Target2D));
    texture->setSize(size.width(), size.height());
}

}  // namespace model