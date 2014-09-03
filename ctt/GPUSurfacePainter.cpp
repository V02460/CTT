#include "GPUSurfacePainter.h"

#include "IOException.h"
#include "FileNotFoundException.h"
#include "OpenGLException.h"
#include "NotImplementedException.h"
#include "IllegalArgumentException.h"
#include "IllegalStateException.h"

// #define WARN_INVALID_UNIFORM

namespace helper {

using ::model::Surface;
using ::helper::VertexAttribute;
using ::exception::OpenGLException;
using ::exception::IOException;
using ::exception::FileNotFoundException;
using ::exception::NotImplementedException;
using ::exception::IllegalArgumentException;
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

void GPUSurfacePainter::initShaderProgram(QString vertexShaderFile, QString fragmentShaderFile) {
    QPair<QString, QOpenGLContext_sptr> cacheKey(fragmentShaderFile, context);

    if (shaderProgramCache.contains(cacheKey)) {
        // get the existing shader from the cache
        program = shaderProgramCache.value(cacheKey);
    } else {
        // create a new shader program
        program.reset(new QOpenGLShaderProgram());

        if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile)) {
            throw OpenGLException("Adding of vertex shader '" +
                                  vertexShaderFile +
                                  "' failed. Log message: " + program->log());
        }

        if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile)) {
            throw OpenGLException("Adding of fragment shader '" +
                                  fragmentShaderFile +
                                  " failed. Log message: " + program->log());
        }

        if (!program->link()) {
            throw OpenGLException("Linking of shader program failed. Log message: " + program->log());
        }

        // add the shader to the cache
        shaderProgramCache.insert(cacheKey, program);
    }
}

void GPUSurfacePainter::setValue(QString name, VertexAttribute::sptr texture) {
    // TODO: context check

    vertexAttributes.insert(name, texture);
}


void GPUSurfacePainter::setValue(QString name, Surface::sptr texture) {
    if (context->shareGroup() != texture->shareGroup()) {
        throw OpenGLException(
            "Context of texture argument does not share resources with context of GPUSurfacePainter.");
    }

    if (textureNames.contains(name)) { // texture name already used - reassign
        int textureIndex = textures.indexOf(textureNames.value(name));

        textures[textureIndex] = texture;

    } else { // new texture

        int textureIndex = textures.size();

        // check number of available texture units
        int maxTextureUnits;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
        if (textureIndex + 1 > maxTextureUnits) {
            throw OpenGLException("Texture unit count exceeds the maximum.");
        }

        // get location of the uniform in the shader
        GLint textureLocation = glGetUniformLocation(program->programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
        if (textureLocation == -1) {
            // throw OpenGLException("'" + name + "' was set but is not defined in the current shader.");
            qWarning() << name << "was set but is not defined in the current shader.";
        }
#endif

        // bind program to set the uniform
        if (!program->bind()) {
            throw OpenGLException("Could not bind shader program.");
        }

        // set uniform to the proper texture unit
        glUniform1i(textureLocation, textureIndex);
    
        program->release();

        // save the texture to be able to bind it when 'run' is called
        // It's ugly we just keep the handle, but a shared pointer gave us problems in the hierarchy...
        textures.append(texture);
    }
}

void GPUSurfacePainter::setValue(QString name, GLint value) {
    GLint uniformLocation = glGetUniformLocation(program->programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program->bind()) {
        throw OpenGLException("Could not bind shader program->");
    }

    // set the uniform to the given value
    glUniform1i(uniformLocation, value);

    program->release();
}

void GPUSurfacePainter::setValue(QString name, QSize value) {
    GLint uniformLocation = glGetUniformLocation(program->programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program->bind()) {
        throw OpenGLException("Could not bind shader program->");
    }

    // set the uniform to the given value
    glUniform2i(uniformLocation, value.width(), value.height());

    program->release();
}

void GPUSurfacePainter::setValue(QString name, GLfloat value) {
    GLint uniformLocation = glGetUniformLocation(program->programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program->bind()) {
        throw OpenGLException("Could not bind shader program->");
    }

    // set the uniform to the given value
    glUniform1f(uniformLocation, value);

    program->release();
}

void GPUSurfacePainter::setValue(QString name, QVector2D value) {
    GLint uniformLocation = glGetUniformLocation(program->programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program->bind()) {
        throw OpenGLException("Could not bind shader program->");
    }

    // set the uniform to the given value
    glUniform2f(uniformLocation, value.x(), value.y());

    program->release();
}

void GPUSurfacePainter::setValue(QString name, QVector3D value) {
    GLint uniformLocation = glGetUniformLocation(program->programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program->bind()) {
        throw OpenGLException("Could not bind shader program->");
    }

    // set the uniform to the given value
    glUniform3f(uniformLocation, value.x(), value.y(), value.z());

    program->release();
}

void GPUSurfacePainter::setValue(QString name, QVector4D value) {
    GLint uniformLocation = glGetUniformLocation(program->programId(), name.toLatin1().constData());
#ifdef WARN_INVALID_UNIFORM
    if (uniformLocation == -1) {
        // throw OpenGLException("'" + name + "' was set but is not defined in the current shader.");
        qWarning() << name << "was set but is not defined in the current shader.";
    }
#endif

    // bind program to set the uniform
    if (!program->bind()) {
        throw OpenGLException("Could not bind shader program->");
    }

    // set the uniform to the given value
    glUniform4f(uniformLocation, value.x(), value.y(), value.z(), value.w());

    program->release();
}

void GPUSurfacePainter::setTargetTexture(Surface::sptr targetTexture) {
    this->targetTexture = targetTexture;
}

Surface::sptr GPUSurfacePainter::run() {
    if (context->shareGroup() != QOpenGLContext::currentContext()->shareGroup()) {
        throw OpenGLException("Cannot access resources in the currently bound context.");
    }
//     if (targetTexture.isNull()) {
//         throw IllegalStateException("Target texture must be set before calling run.");
//     }
    if (vertexAttributes.isEmpty()) {
        throw new IllegalStateException("At least one vertex attribute must exist to render to the image.");
    }

    QOpenGLFramebufferObject *fbo = nullptr;

    QSize targetSize;

    // render to default screen or to texture?
    if (targetTexture.isNull()) {

        //get the target size
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
         targetSize = QSize(viewport[2], viewport[3]);

        // render to screen
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    } else {

        //get the target size
        targetSize = targetTexture->getSize();

        // enable render to texture
        fbo = targetTexture->getFramebufferObject();

        if (!fbo->isValid()) {
            throw OpenGLException("Framebuffer object is not valid.");
        }
        if (!fbo->bind()) {
            throw OpenGLException("Could not bind framebuffer object.");
        }
    }

    // make target size available in the shader
    setValue("_targetSize", targetSize);

    // set the viewport to the target texture size
    glViewport(0, 0, targetSize.width(), targetSize.height());

    // prepare
    if (!program->bind()) {
        throw OpenGLException("Could not bind shader program.");
    }
    bindAttributeArrays();
    bindTextures();

    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, getVertexCount());

    // cleanup
    releaseTextures();
    releaseAttributeArrays();
    program->release();

    if (fbo != nullptr) {
        fbo->release();
    }

    return targetTexture;
}

void GPUSurfacePainter::fill(QColor color) {
    glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    glClear(GL_COLOR_BUFFER_BIT);
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
    for (auto i = vertexAttributes.begin(); i != vertexAttributes.end(); i++) {
        VertexAttribute::sptr attribute = i.value();
        QString name = i.key();

        attribute->bind();

        program->enableAttributeArray(name.toLatin1().constData());
        // TODO: rewrite to use vertexLocation
        //if (vertexLocation == -1) {
        //    throw OpenGLException("Vertex shader has no \"" + vertexPositionStr + "\" attribute to assign vertex "
        //                                   "positions to.");
        //}

        program->setAttributeBuffer(name.toLatin1().constData(),
                                    attribute->getType(),
                                    0,
                                    attribute->getTupelSize());
    }
}

inline void GPUSurfacePainter::releaseAttributeArrays() {
    for (auto i = vertexAttributes.begin(); i != vertexAttributes.end(); i++) {
        QString name = i.key();
        program->disableAttributeArray(name.toLatin1().constData());
    }
}

unsigned int GPUSurfacePainter::getVertexCount() {
    unsigned int vertexCount = std::numeric_limits<unsigned int>::max();

    for (auto i = vertexAttributes.begin(); i != vertexAttributes.end(); i++) {
        VertexAttribute::sptr attribute = i.value();
        vertexCount = qMin(vertexCount, attribute->getVertexCount());
    }

    return vertexCount;
}


QMap<QPair<QString, QOpenGLContext_sptr>, QOpenGLShaderProgram_sptr> GPUSurfacePainter::shaderProgramCache;

}  // namespace helper