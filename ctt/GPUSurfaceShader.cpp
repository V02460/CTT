#include "GPUSurfaceShader.h"

#include "IOException.h"
#include "FileNotFoundException.h"
#include "OpenGLException.h"
#include "NotImplementedException.h"
#include "IllegalStateException.h"

// #define WARN_INVALID_UNIFORM

namespace helper {

using ::model::Surface;
using ::exception::OpenGLException;
using ::exception::IOException;
using ::exception::FileNotFoundException;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;

GPUSurfaceShader::GPUSurfaceShader(QString fragmentShaderFile, 
                                   Surface::sptr sourceTexture)
        : GPUSurfaceShader(fragmentShaderFile, sourceTexture->getContext()) {
    setSourceTexture(sourceTexture);
}

GPUSurfaceShader::GPUSurfaceShader(QString fragmentShaderFile,
                                   QSharedPointer<QOpenGLContext> context)
        : GPUSurfacePainter(":/Shader/Default/Default.vs",
                            fragmentShaderFile,
                            context)
        , sourceTexture()
        , positionAttribute(new VertexAttribute(4, 2)) {

    // vertex coordinates for a screen filling quad
    *positionAttribute << -1.f <<  1.f
                       <<  1.f <<  1.f
                       << -1.f << -1.f
                       <<  1.f << -1.f;
}

Surface::sptr GPUSurfaceShader::run() {
    if (sourceTexture.isNull()) {
        throw new IllegalStateException("Source texture must be set before calling run.");
    }

    setTargetTexture(Surface::sptr(new Surface(getContext(), sourceTexture->getSize())));

    return applyShader();
}

Surface::sptr GPUSurfaceShader::run(QSize targetSize) {
    if (sourceTexture.isNull()) {
        throw new IllegalStateException("Source texture must be set before calling run.");
    }

    // create the target texture
    setTargetTexture(Surface::sptr(new Surface(getContext(), targetSize)));

    return applyShader();
}

Surface::sptr GPUSurfaceShader::applyShader() {
    setValue("_sourceTexture", sourceTexture);
    setValue("_sourceSize", sourceTexture->getSize());
    setValue("_pos", positionAttribute);

    return GPUSurfacePainter::run();
}

void GPUSurfaceShader::setSourceTexture(Surface::sptr sourceTexture) {
    this->sourceTexture = sourceTexture;
}

Surface::sptr GPUSurfaceShader::getSourceTexture() {
    return sourceTexture;
}

}  // namespace helper