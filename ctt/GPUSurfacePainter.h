#ifndef _GPUSURFACEPAINTER_H
#define _GPUSURFACEPAINTER_H

#include <QSharedPointer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QSize>
#include <QOpenGLFunctions>
#include <QColor>

#include "Surface.h"
#include "VertexAttribute.h"

namespace helper {

typedef QSharedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_sptr;
typedef QSharedPointer<QOpenGLShader> QOpenGLShader_sptr;
typedef QSharedPointer<QOpenGLShaderProgram> QOpenGLShaderProgram_sptr;
typedef QSharedPointer<QOpenGLContext> QOpenGLContext_sptr;

class GPUSurfacePainter : protected QOpenGLFunctions {
public:
    typedef QScopedPointer<GPUSurfacePainter> uptr;
    typedef QSharedPointer<GPUSurfacePainter> sptr;
    typedef QWeakPointer<GPUSurfacePainter> wptr;

    /**
     * Creates a new GPUSurfacePainter which will apply the given filter to a texture when run.
     *
     * @param vertexShaderFile File containing the vertex shader source for the executed shader program
     * @param fragmentShaderFile File containing the fragment shader source for the executed shader program
     * @param context The context in which to operate and the target texture will be generated in
     */
    GPUSurfacePainter(QString vertexShaderFile,
                      QString fragmentShaderFile,
                      QSharedPointer<QOpenGLContext> context);

    /**
     * Destroys the GPUSurfacePainter.
     */
    ~GPUSurfacePainter() {}

    /**
     * Set the shader uniform variable of the given name to the given value.
     * 
     * @throws OpenGLException when the associated shader program can not be bound
     */
    void setValue(QString name, ::helper::VertexAttribute::sptr attribute);
    void setValue(QString name, ::model::Surface::sptr texture);
    void setValue(QString name, GLint value);
    void setValue(QString name, QSize value);
    void setValue(QString name, GLfloat value);
    void setValue(QString name, QVector2D value);
    void setValue(QString name, QVector3D value);
    void setValue(QString name, QVector4D value);
    
    /**
     * Sets the target texture.
     *
     * @param targetTexture the new target texture
     */
    void setTargetTexture(::model::Surface::sptr targetTexture);

    /**
     * Executes the set up operations by executing the shader.
     */
    virtual ::model::Surface::sptr run();

    void fill(QColor color);
protected:
    QSharedPointer<QOpenGLContext> getContext();
    ::model::Surface::sptr getTargetTexture();

private:
    Q_DISABLE_COPY(GPUSurfacePainter);

    void initShaderProgram(QString vertexShaderFile, QString fragmentShaderFile);

    inline void bindTextures();
    inline void releaseTextures();
    inline void bindAttributeArrays();
    inline void releaseAttributeArrays();

    unsigned int getVertexCount();

    QSharedPointer<QOpenGLShaderProgram> program;
    QList<::model::Surface::sptr> textures;
    QSharedPointer<QOpenGLContext> context;
    ::model::Surface::sptr targetTexture;
    QMap<QString, ::model::Surface::sptr> textureNames;
    static QMap<QPair<QString, QOpenGLContext_sptr>, QOpenGLShaderProgram_sptr> shaderProgramCache;

    QMap<QString, VertexAttribute::sptr> vertexAttributes;
};

}  // namespace helper

#endif  // _GPUSURFACEPAINTER_H