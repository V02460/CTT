#include "GPUSurfacePainter.h"

#include "IOException.h"
#include "FileNotFoundException.h"
#include "OpenGLException.h"
#include "NotImplementedException.h"
#include "IllegalStateException.h"

// #define WARN_INVALID_UNIFORM

namespace helper {

using ::model::Surface;
using ::helper::VertexAttribute;
using ::exception::OpenGLException;
using ::exception::IOException;
using ::exception::FileNotFoundException;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;

static QSize getNewSizeDefault(QSize size) {
    return QSize(size.width() / 2, size.height() / 2);
}

GPUSurfacePainter::GPUSurfacePainter(QString vertexShaderFile, 
                                     QString fragmentShaderFile,
                                     QSharedPointer<QOpenGLContext> context)
        : targetTexture()
        , context(context) {
    initializeOpenGLFunctions();
    initShaderProgram(vertexShaderFile, fragmentShaderFile);
}

void GPUSurfacePainter::initShaderProgram(QString vertexShaderFile , QString fragmentShaderFile) {
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile)) {
        throw new OpenGLException("Adding of vertex shader failed. Log message: " + program.log());
    }

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile)) {
        throw new OpenGLException("Adding of fragment shader failed. Log message: " + program.log());
    }

    if (!program.link()) {
        throw new OpenGLException("Linking of shader program failed. Log message: " + program.log());
    }
}

void GPUSurfacePainter::setValue(QString name, VertexAttribute::sptr texture) {
    throw new NotImplementedException();
}

void GPUSurfacePainter::setValue(QString name, Surface::sptr texture) {
    if (context->shareGroup() != texture->shareGroup()) {
        throw new OpenGLException(
            "Context of texture argument does not share resources with context of GPUSurfacePainter.");
    }

    // TODO: make reassign work

    int textureIndex = textures.size();

    // check number of available texture units
    int maxTextureUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
    if (textureIndex + 1 > maxTextureUnits) {
        throw new OpenGLException("Texture unit count exceeds the maximum.");
    }

    // get location of the uniform in the shader
    GLint textureLocation = glGetUniformLocation(program.programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (textureLocation == -1) {
        // throw new OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // set uniform to the proper texture unit
    glUniform1i(textureLocation, textureIndex);
    
    program.release();

    // save the texture to be able to bind it when 'run' is called
    // It's ugly we just keep the handle, but a shared pointer gave us problems in the hierarchy...
    textures.append(texture);
}

void GPUSurfacePainter::setValue(QString name, GLint value) {
    GLint uniformLocation = glGetUniformLocation(program.programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw new OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // set the uniform to the given value
    glUniform1i(uniformLocation, value);

    program.release();
}

void GPUSurfacePainter::setValue(QString name, QSize value) {
    GLint uniformLocation = glGetUniformLocation(program.programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw new OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // set the uniform to the given value
    glUniform2i(uniformLocation, value.width(), value.height());

    program.release();
}

void GPUSurfacePainter::setValue(QString name, GLfloat value) {
    GLint uniformLocation = glGetUniformLocation(program.programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw new OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // set the uniform to the given value
    glUniform1f(uniformLocation, value);

    program.release();
}

void GPUSurfacePainter::setValue(QString name, QVector2D value) {
    GLint uniformLocation = glGetUniformLocation(program.programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw new OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // set the uniform to the given value
    glUniform2f(uniformLocation, value.x(), value.y());

    program.release();
}

void GPUSurfacePainter::setValue(QString name, QVector3D value) {
    GLint uniformLocation = glGetUniformLocation(program.programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw new OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // set the uniform to the given value
    glUniform3f(uniformLocation, value.x(), value.y(), value.z());

    program.release();
}

void GPUSurfacePainter::setValue(QString name, QVector4D value) {
    GLint uniformLocation = glGetUniformLocation(program.programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw new OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // set the uniform to the given value
    glUniform4f(uniformLocation, value.x(), value.y(), value.z(), value.w());

    program.release();
}

void GPUSurfacePainter::setTargetTexture(Surface::sptr targetTexture) {
    this->targetTexture = targetTexture;
}

Surface::sptr GPUSurfacePainter::run() {
    if (context->shareGroup() != QOpenGLContext::currentContext()->shareGroup()) {
        throw new OpenGLException("Cannot access resources in the currently bound context.");
    }
    if (targetTexture.isNull()) {
        throw new IllegalStateException("Target texture must be set before calling run.");
    }

    // make target size available in the shader
    setValue("_targetSize", targetTexture->getSize());

    // enable render to texture
    QOpenGLFramebufferObject *fbo = targetTexture->getFramebufferObject();

    if (!fbo->isValid()) {
        throw new OpenGLException("Framebuffer object is not valid.");
    }
    if (!fbo->bind()) {
        throw new OpenGLException("Could not bind framebuffer object.");
    }

    // prepare
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }
    bindAttributeArrays();
    bindTextures();
   
    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // cleanup
    releaseTextures();
    releaseAttributeArrays();
    program.release();

    fbo->release();

    return targetTexture;
}

QSharedPointer<QOpenGLContext> GPUSurfacePainter::getContext() {
    return context;
}

inline void GPUSurfacePainter::bindTextures() {
    unsigned int textureCnt = textures.size();
    for (unsigned int i = 0; i < textureCnt; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        GLuint textureHandle = textures.at(i)->getTextureHandle();
        glBindTexture(GL_TEXTURE_2D, textureHandle);
    }
}

inline void GPUSurfacePainter::releaseTextures() {
    unsigned int textureCnt = textures.size();
    for (unsigned int i = 0; i < textureCnt; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

inline void GPUSurfacePainter::bindAttributeArrays() {
    // vertex coordinates for a screen filling quad
    static const QVector2D vertices[] = {{-1.f,  1.f},
                                         { 1.f,  1.f},
                                         {-1.f, -1.f},
                                         { 1.f, -1.f}};

    // setup vertex position attribute
    static const QString vertexPositionStr = "_pos";
    int vertexLocation = program.attributeLocation(vertexPositionStr);
    if (vertexLocation == -1) {
        throw new OpenGLException("Vertex shader has no \"" + vertexPositionStr + "\" attribute to assign vertex "
                                  "positions to.");
    }
    program.enableAttributeArray(vertexLocation);
    program.setAttributeArray(vertexLocation, vertices);
}

inline void GPUSurfacePainter::releaseAttributeArrays() {
    //program.disableAttributeArray(vertexLocation);
}

}  // namespace helper