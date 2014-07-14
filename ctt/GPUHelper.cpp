#include "GPUHelper.h"

namespace helper {

using ::model::Surface;
using ::exception::OpenGLException;

GPUHelper::sptr GPUHelper::instance() {
    if (!helperInstance) {
        helperInstance = GPUHelper::sptr(new GPUHelper());
    }

    return helperInstance;
}

QOpenGLShader_sptr GPUHelper::getDefaultFlatVS() {
    
    QOpenGLShader_sptr shader(new QOpenGLShader(QOpenGLShader::Vertex));

    bool success = shader->compileSourceCode(R"(
        attribute vec2 _pos;
        varying vec2 texcrd;

        void main() {
            texcrd = (_pos + 1.f) * 0.5f;

            gl_Position = vec4(_pos, 0.0, 0.0);
        }
    )");

    if (!success) {
        throw new OpenGLException("Unable to compile Vertex Shader.");
    }

    return shader;
}

void GPUHelper::runShader(Surface *target, QOpenGLShaderProgram *program) {

    QOpenGLFramebufferObject *fbo = target->getFramebufferObject();

    // vertex coordinates for a screen filling quad
    GLfloat vertices[] = {
        -1.f, 1.f,
        1.f, 1.f,
        -1.f, -1.f,
        1.f, -1.f};

    // set state
    fbo->bind();
    glEnableVertexAttribArray(0);
    program->bind();

    // index, size, type, normalized, stride, pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &vertices);

    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // cleanup state
    program->release();
    glDisableVertexAttribArray(0);
    fbo->release();
}

Surface::sptr GPUHelper::compactTexture(const Surface &sourceTexture,
                                        QOpenGLShaderProgram *compactionProgram,
                                        QSize(&getNewSize)(QSize),
                                        QSize targetSize) {

    QSize oldSize;
    QSize newSize = sourceTexture.getSize();

    Surface::sptr target;

    GLuint sourceTextureHandle = sourceTexture.getTextureHandle();

    do {
        oldSize = newSize;
        newSize = getNewSize(newSize);

        target.reset(new Surface(sourceTexture.context, newSize));

        compactionProgram->setUniformValue("sourceSize", oldSize);
        compactionProgram->setUniformValue("targetSize", newSize);
        compactionProgram->setUniformValue("sourceImage", sourceTextureHandle);

        runShader(target.data(), compactionProgram);

        sourceTextureHandle = target->getTextureHandle();

    } while (newSize.width() > targetSize.width() ||
             newSize.height() > targetSize.height());

    return target;    
}

GPUHelper::GPUHelper() {
    initializeOpenGLFunctions();
}

GPUHelper::sptr GPUHelper::helperInstance;

}