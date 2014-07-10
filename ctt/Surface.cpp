#include "Surface.h"

namespace model {

Surface::Surface(QSharedPointer<QOpenGLContext> glContext, QSize size)
        : glContext(glContext)
        , glTexture(QOpenGLTexture::Target2D) {

    glTexture.setSize(size.width(), size.height());
    glTexture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
}

const QOpenGLTexture &Surface::getGLTexture() const {
    return glTexture;
}

QSharedPointer<QOpenGLContext> Surface::getContext() {
    return glContext;
}



}  // namespace model