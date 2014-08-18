#include "GPUHelper.h"

#include <QFile>

#include "IOException.h"
#include "FileNotFoundException.h"
#include "OpenGLException.h"
#include "NotImplementedException.h"

// #define WARN_INVALID_UNIFORM

namespace helper {

using ::model::Surface;
using ::exception::OpenGLException;
using ::exception::IOException;
using ::exception::FileNotFoundException;
using ::exception::NotImplementedException;

static QSize getNewSizeDefault(QSize size) {
    return QSize(size.width() / 2, size.height() / 2);
}

GPUHelper::GPUHelper(QString fragmentShaderFile, QSharedPointer<QOpenGLContext> context)
        : mode(APPLY)
        , context(context)
        , getNewSize(getNewSizeDefault) {
    initializeOpenGLFunctions();
    initShaderProgram(fragmentShaderFile);
}

GPUHelper::GPUHelper(QString fragmentShaderFile, QSharedPointer<QOpenGLContext> context, QSize(&getNewSize)(QSize))
        : mode(COMPACT)
        , context(context)
        , getNewSize(getNewSize) {
    initializeOpenGLFunctions();
    initShaderProgram(fragmentShaderFile);
}

void GPUHelper::initShaderProgram(QString fragmentShaderFile) {
    QSharedPointer<QOpenGLShader> vertexShader = GPUHelper::getDefaultFlatVS();
    if (!program.addShader(vertexShader.data())) {
        throw new OpenGLException("Adding of vertex shader failed. Log message: " + program.log());
    }

    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile)) {
        throw new OpenGLException("Adding of fragment shader failed. Log message: " + program.log());
    }

    if (!program.link()) {
        throw new OpenGLException("Linking of shader program failed. Log message: " + program.log());
    }
}

void GPUHelper::setValue(QString name, const Surface &texture) {
    if (context->shareGroup() != texture.shareGroup()) {
        throw new OpenGLException("Context of texture argument does not share resources with context of GPUHelper.");
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
    textures.append(texture.getTextureHandle());
}

void GPUHelper::setValue(QString name, GLint value) {
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

void GPUHelper::setValue(QString name, QSize value) {
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

void GPUHelper::setValue(QString name, GLfloat value) {
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

void GPUHelper::setValue(QString name, QVector2D value) {
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

void GPUHelper::setValue(QString name, QVector3D value) {
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

void GPUHelper::setValue(QString name, QVector4D value) {
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

Surface::sptr GPUHelper::run(const Surface &sourceTexture, QSize targetSize) {
    switch (mode) {
        case APPLY:
            return applyShader(sourceTexture, targetSize);
            break;
        case COMPACT:
            return compactTexture(sourceTexture, targetSize);
            break;
        default:
            throw new NotImplementedException("The mode " + QString::number(mode) + " is not implemented.");
            break;
    }
}

Surface::sptr GPUHelper::applyShader(const Surface &sourceTexture, QSize targetSize) {
    if (context->shareGroup() != QOpenGLContext::currentContext()->shareGroup()) {
        throw new OpenGLException("Cannot access resources in the currently bound context.");
    }

    setValue("_sourceTexture", sourceTexture);
    setValue("_sourceSize", sourceTexture.getSize());
    setValue("_targetSize", targetSize);

    // create the target texture
    Surface::sptr target(new Surface(context, targetSize));

    // enable render to texture
    QOpenGLFramebufferObject *fbo = target->getFramebufferObject();

    if (!fbo->isValid()) {
        throw new OpenGLException("Framebuffer object is not valid.");
    }

    if (!fbo->bind()) {
        throw new OpenGLException("Could not bind framebuffer object.");
    }

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

    // bind all the textures
    unsigned int textureCnt = textures.size();
    for (unsigned int i = 0; i < textureCnt; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        GLuint textureHandle = textures.at(i);
        glBindTexture(GL_TEXTURE_2D, textureHandle);
    }

    // bind the shader program for drawing
    if (!program.bind()) {
        throw new OpenGLException("Could not bind shader program.");
    }

    // draw
    //glClearColor(0.f, 0.f, 0.8f, 1.f);
    //glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // cleanup
    program.disableAttributeArray(vertexLocation);
    program.release();

    fbo->release();

    return target;
}

QOpenGLShader_sptr GPUHelper::getDefaultFlatVS() {
    
    QOpenGLShader_sptr shader(new QOpenGLShader(QOpenGLShader::Vertex));

    bool success = shader->compileSourceCode(R"(#version 130

        attribute vec2 _pos;
        varying vec2 texcrd;

        void main() {
            texcrd = (_pos + 1.f) * 0.5f;

            gl_Position = vec4(_pos, 0.f, 1.f);
        }
    )");

    if (!success) {
        throw new OpenGLException("Unable to compile Vertex Shader: " + shader->log());
    }

    return shader;
}



Surface::sptr GPUHelper::compactTexture(const Surface &sourceTexture, QSize targetSize) {
    QSize oldSize;
    QSize newSize = sourceTexture.getSize();

    Surface::sptr target;

    const Surface *sourceTextureHandle = &sourceTexture;

    int iteration = 0;

    do {
        oldSize = newSize;
        newSize = getNewSize(newSize);

        setValue("_iteration", iteration++);

        target = applyShader(*sourceTextureHandle, newSize);

        // get ready for the next round by making target texture to source
        sourceTextureHandle = target.data();

    // repeat until we reach target size
     } while (newSize.width() > targetSize.width() ||
              newSize.height() > targetSize.height());
    //} while (iteration < 1);

    return target;
}

}