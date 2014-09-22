#include "GPUSurfaceCompactor.h"

#include "IOException.h"
#include "FileNotFoundException.h"
#include "OpenGLException.h"

// #define WARN_INVALID_UNIFORM

namespace helper {

using ::model::Surface;
using ::exception::OpenGLException;
using ::exception::IOException;
using ::exception::FileNotFoundException;

QSize getNewSizeDefault(QSize size) {
    return QSize(size.width() / 2, size.height() / 2);
}

GPUSurfaceCompactor::GPUSurfaceCompactor(QString fragmentShaderFile,
                                         Surface::sptr sourceTexture,
                                         QSize(&getNewSize)(QSize))
        : GPUSurfaceCompactor(fragmentShaderFile, sourceTexture->getContext(), getNewSize) {
    setSourceTexture(sourceTexture);
}

GPUSurfaceCompactor::GPUSurfaceCompactor(QString fragmentShaderFile,
                                         QSharedPointer<QOpenGLContext> context,
                                         QSize(&getNewSize)(QSize))
        : GPUSurfaceShader(fragmentShaderFile, context)
        , getNewSize(getNewSize) {
}

Surface::sptr GPUSurfaceCompactor::run() {
    return run(getSourceTexture()->getSize());
}

Surface::sptr GPUSurfaceCompactor::run(QSize targetSize) {
    Surface::sptr initialSourceTexture = getSourceTexture();

    Surface::sptr targetTexture;
    QSize newSize = initialSourceTexture->getSize();

    int iteration = 0;

    do {
        newSize = getNewSize(newSize);

        setValue("_iteration", iteration++);

        targetTexture = GPUSurfaceShader::run(newSize);

        // get ready for the next round by making target texture to source
        setSourceTexture(targetTexture);

    // repeat until we reach target size
     } while (newSize.width() > targetSize.width() ||
              newSize.height() > targetSize.height());
    
    // restore the primitive state
    setSourceTexture(initialSourceTexture);

    return targetTexture;
}

}  // namespace helper