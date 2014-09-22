#include "GPUSurfaceShader.h"

#include "IOException.h"
#include "FileNotFoundException.h"
#include "OpenGLException.h"
#include "IllegalStateException.h"

// #define WARN_INVALID_UNIFORM

namespace helper {

using ::model::Surface;
using ::exception::OpenGLException;
using ::exception::IOException;
using ::exception::FileNotFoundException;
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
        , positionAttribute(new VertexAttribute(4, 2))
        , texcrdAttribute(new VertexAttribute(4, 2)) {

    setPositionAttribute();
    setTexcrdAttribute();
}

Surface::sptr GPUSurfaceShader::run() {
    if (sourceTexture.isNull()) {
        throw IllegalStateException("Source texture must be set before calling run.");
    }

    setTargetTexture(Surface::sptr(new Surface(getContext(), sourceTexture->getSize())));

    return applyShader();
}

Surface::sptr GPUSurfaceShader::run(QSize targetSize) {
    if (sourceTexture.isNull()) {
        throw IllegalStateException("Source texture must be set before calling run.");
    }

    // create the target texture
    setTargetTexture(Surface::sptr(new Surface(getContext(), targetSize)));

    return applyShader();
}

Surface::sptr GPUSurfaceShader::applyShader() {
    setValue("_sourceTexture", sourceTexture);
    setValue("_sourceSize", sourceTexture->getSize());
    setValue("_pos", positionAttribute);
    setValue("_tex", texcrdAttribute);

    return GPUSurfacePainter::run();
}

void GPUSurfaceShader::setSourceTexture(Surface::sptr sourceTexture) {
    this->sourceTexture = sourceTexture;
}

void GPUSurfaceShader::invertY(bool invert) {
    this->invert = invert;
    setPositionAttribute();
}

Surface::sptr GPUSurfaceShader::getSourceTexture() {
    if (sourceTexture.isNull()) {
        throw IllegalStateException("Source texture was not set.");
    }

    return sourceTexture;
}

void GPUSurfaceShader::setPositionAttribute() {
    float y = invert ? -1.f : 1.f;

    // vertex coordinates for a screen filling quad
    *positionAttribute << -1.f <<  y
                       <<  1.f <<  y
                       << -1.f << -y
                       <<  1.f << -y;
}

void GPUSurfaceShader::setTexcrdAttribute() {
    *texcrdAttribute << 0.f << 1.f
                     << 1.f << 1.f
                     << 0.f << 0.f
                     << 1.f << 0.f;
}

}  // namespace helper