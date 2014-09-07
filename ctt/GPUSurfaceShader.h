#ifndef _GPUHELPER_H
#define _GPUHELPER_H

#include <QSharedPointer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QSize>
#include <QOpenGLFunctions>

#include "Surface.h"
#include "GPUSurfacePainter.h"
#include "VertexAttribute.h"

namespace helper {

typedef QSharedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_sptr;
typedef QSharedPointer<QOpenGLShader> QOpenGLShader_sptr;
typedef QSharedPointer<QOpenGLContext> QOpenGLContext_sptr;

class GPUSurfaceShader : public GPUSurfacePainter {
public:
    typedef QScopedPointer<GPUSurfaceShader> uptr;
    typedef QSharedPointer<GPUSurfaceShader> sptr;
    typedef QWeakPointer<GPUSurfaceShader> wptr;

    /**
     * Creates a new GPUSurfaceShader which will apply the given filter to a texture when run.
     *
     * @param fragmentShaderFile File containing the fragment shader source for the executed shader program
     * @param sourceTexture The source image data used to create the new texture
     */
    GPUSurfaceShader(QString fragmentShaderFile,
                     ::model::Surface::sptr sourceTexture);

    /**
     * Creates a new GPUSurfaceShader which will apply the given filter to a texture when run.
     * setSourceTexture() must be called before executing with run()
     *
     * @param fragmentShaderFile File containing the fragment shader source for the executed shader program
     * @param context The context in which to operate and the target texture will be generated in
     */
    GPUSurfaceShader(QString fragmentShaderFile,
                     QSharedPointer<QOpenGLContext> context);

    /**
     * Destroys the GPUSurfaceShader.
     */
    ~GPUSurfaceShader() {}

    /**
     * Executes the set up operations by executing the shader.
     * Uses sourceTexture and targetSize set by their setter methods or previous calls to the run method with arguments.
     *
     * @return a new texture filled with the result of the shading operation
     */
    virtual ::model::Surface::sptr run();

    /**
     * Executes the set up operations by executing the shader.
     *
     * @param targetSize the size of the returned texture
     * @return a new texture filled with the result of the shading operation
     */
    virtual ::model::Surface::sptr run(QSize targetSize);

    /**
     * Set the source texture.
     *
     * @param sourceTexture texture which is bound to the _sourceTexture shader uniform
     */
    void setSourceTexture(::model::Surface::sptr sourceTexture);

    /**
     * Controls if y-axis of the texture is inverted.
     *
     * @param invert set to true if texture should be mirrored on its y-axis
     */
    void invertY(bool invert);

protected:
    /**
    * Returns the source texture.
    *
    * @return texture which is bound to the _sourceTexture shader uniform
    */
    ::model::Surface::sptr getSourceTexture();

private:
    Q_DISABLE_COPY(GPUSurfaceShader);

    /**
    * Returns a default vertex shader which passes through position and texture coordinates.
    *
    * @return QSharedPointer<QOpenGLShader> default shader
    */
    static QOpenGLShader_sptr getDefaultFlatVS();

    ::model::Surface::sptr applyShader();

    void setPositionAttribute();
    void setTexcrdAttribute();

    VertexAttribute::sptr positionAttribute;
    VertexAttribute::sptr texcrdAttribute;

    ::model::Surface::sptr sourceTexture;

    bool invert = false;
};

}  // namespace helper

#endif  // _GPUHELPER_H