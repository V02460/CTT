#ifndef _GPUHELPER_H
#define _GPUHELPER_H

#include <QSharedPointer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QSize>
#include <QOpenGLFunctions>
#include <QPair>

#include "Surface.h"

namespace helper {

typedef QSharedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_sptr;
typedef QSharedPointer<QOpenGLShader> QOpenGLShader_sptr;
typedef QSharedPointer<QOpenGLContext> QOpenGLContext_sptr;

class GPUHelper : protected QOpenGLFunctions {
public:
    typedef QScopedPointer<GPUHelper> uptr;
    typedef QSharedPointer<GPUHelper> sptr;
    typedef QWeakPointer<GPUHelper> wptr;

    /**
     * Creates a new GPUHelper which will apply the given filter to a texture when run.
     *
     * @param fragmentShaderFile File containing the fragment shader source for the executed shader program
     * @param context The context in which to operate and the target texture will be generated in
     */
    GPUHelper::GPUHelper(QString fragmentShaderFile, QSharedPointer<QOpenGLContext> context);

    /**
     * Creates a new GPUHelper which will perform a compaction on a texture using the given size function when run.
     * Compaction means the repeated collapse of a source texture to a smaller size until it reaches a target size.
     * The run method returns when it generates a texture with dimensions smaller or equal to targetSize
     *
     * @param fragmentShaderFile File containing the fragment shader source for the executed shader program
     * @param context The context in which to operate and the target texture will be generated in
     * @param getNewSize Function that is called to determine the target size of the next iteration
     *        It must converge to a value equal or smaller than the target size given to 'run' when called recursive
     */
    GPUHelper::GPUHelper(QString fragmentShaderFile, QSharedPointer<QOpenGLContext> context, QSize(&getNewSize)(QSize));

    /**
     * Destroys the GPUHelper.
     */
    ~GPUHelper() {}

    /**
     * Set the shader uniform variable of the given name to the given value.
     * 
     * @throws OpenGLException when the associated shader program can not be bound
     */
    void setValue(QString name, const ::model::Surface &texture);
    void setValue(QString name, GLint value);
    void setValue(QString name, QSize value);
    void setValue(QString name, GLfloat value);
    void setValue(QString name, QVector2D value);
    void setValue(QString name, QVector3D value);
    void setValue(QString name, QVector4D value);

    /**
     * Executes the set up operations by executing the shader.
     *
     * @param sourceTexture texture which is bound to the _sourceTexture shader uniform
     * @param targetSize APPLY: the size of the returned texture
     *                   COMPACT: the size to which the texture must at least be shrunken
     */
    ::model::Surface::sptr run(const ::model::Surface &sourceTexture, QSize targetSize);

    /**
    * Executes the set up operations by executing the shader.
    * The target texture dimensions matches those of the source texture.
    *
    * @param sourceTexture texture which is bound to the _sourceTexture shader uniform
    */
    ::model::Surface::sptr run(const ::model::Surface &sourceTexture);

private:
    enum OperationMode {
        APPLY,
        COMPACT
    };

    void initShaderProgram(QString fragmentShaderFile);

    ::model::Surface::sptr applyShader(const ::model::Surface &sourceTexture, QSize targetSize);

    ::model::Surface::sptr compactTexture(const ::model::Surface &sourceTexture, QSize targetSize);

    /**
    * Returns a default vertex shader which can be used in conjunction with applyShader().
    *
    * @return QSharedPointer<QOpenGLShader> default shader
    */
    static QOpenGLShader_sptr getDefaultFlatVS();

    QSharedPointer<QOpenGLShaderProgram> program;
    QList<GLuint> textures;
    QMap<QString, GLuint> textureNames;
    QSharedPointer<QOpenGLContext> context;
    OperationMode mode;
    QSize (&getNewSize)(QSize);
    static QMap<QPair<QString, QSharedPointer<QOpenGLContext>>, QSharedPointer<QOpenGLShaderProgram>> shaderProgramCache;
};

}  // namespace helper

#endif  // _GPUHELPER_H