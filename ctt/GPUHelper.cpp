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
        attribute vec2 pos;
        varying vec2 texcrd;

        void main() {
            texcrd = (pos + 1.f) * 0.5f;

            gl_Position = vec4(pos, 0.f, 0.f);
        }
    )");

    if (!success) {
        throw new OpenGLException("Unable to compile Vertex Shader: " + shader->log());
    }

    return shader;
}

void GPUHelper::runShader(Surface *target, QOpenGLShaderProgram *program) {

    QOpenGLFramebufferObject *fbo = target->getFramebufferObject();

    if (!fbo->isValid()) {
        throw new OpenGLException("Framebuffer object is not valid.");
    }

    // set state
    if (!fbo->bind()) {
        throw new OpenGLException("Could not bind framebuffer object.");
    }
    
    if (!program->bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // vertex coordinates for a screen filling quad
    static const QVector2D vertices[] = {{-0.f,  0.f},
                                         { 1.f,  1.f},
                                         {-1.f, -1.f},
                                         { 1.f, -1.f}};
    
    // draw with different rotation
    /*static const QVector2D vertices[] = {{-1.f, 1.f},
                                         {-1.f, -1.f},
                                         { 1.f, 1.f},
                                         { 1.f, -1.f}};*/

    /*static const GLfloat vertices[] = {-1.f,  1.f,
                                        1.f,  1.f,
                                       -1.f, -1.f,
                                        1.f, -1.f};*/

    int vertexLocation = program->attributeLocation("pos");
    if (vertexLocation == -1) {
        throw new OpenGLException("Vertex shader has no \"_pos\" attribute to assign vertex positions to.");
    }
    qDebug() << "attribute location of \"_pos\": " + QString::number(vertexLocation);

    program->enableAttributeArray(vertexLocation);

    //program->setAttributeArray(vertexLocation, vertices);
    program->setAttributeArray(vertexLocation, vertices);
    // index, size, type, normalized, stride, pointer
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &vertices);

    qDebug() << program->log();
    qDebug() << "Number of linked shaders in program: " + QString::number(program->shaders().size());

    // draw
    glClearColor(0.f, 0.8f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // cleanup state
    program->disableAttributeArray(vertexLocation);
    program->release();

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