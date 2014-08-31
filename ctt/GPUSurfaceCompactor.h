#ifndef _GPUSURFACECOMPACTOR_H
#define _GPUSURFACECOMPACTOR_H

#include <QSharedPointer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QSize>
#include <QOpenGLFunctions>

#include "Surface.h"
#include "GPUSurfaceShader.h"

namespace helper {

typedef QSharedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_sptr;
typedef QSharedPointer<QOpenGLShader> QOpenGLShader_sptr;
typedef QSharedPointer<QOpenGLContext> QOpenGLContext_sptr;

class GPUSurfaceCompactor : public GPUSurfaceShader {
public:
    typedef QScopedPointer<GPUSurfaceCompactor> uptr;
    typedef QSharedPointer<GPUSurfaceCompactor> sptr;
    typedef QWeakPointer<GPUSurfaceCompactor> wptr;

    /**
     * Creates a new GPUSurfaceCompactor which will perform a compaction on a texture using the given size function
     * when run.
     * Compaction means the repeated collapse of a source texture to a smaller size until it reaches a target size.
     * The run method returns when it generates a texture with dimensions smaller or equal to targetSize
     *
     * @param fragmentShaderFile File containing the fragment shader source for the executed shader program
     * @param sourceTexture texture which is made available to the shader
     * @param getNewSize Function that is called to determine the target size of the next iteration
     *        It must converge to a value equal or smaller than the target size given to 'run' when called recursive
     */
    GPUSurfaceCompactor(QString fragmentShaderFile,
                        ::model::Surface::sptr sourceTexture,
                        QSize(&getNewSize)(QSize));

    /**
     * Creates a new GPUSurfaceCompactor which will perform a compaction on a texture using the given size function
     * when run.
     * Compaction means the repeated collapse of a source texture to a smaller size until it reaches a target size.
     * The run method returns when it generates a texture with dimensions smaller or equal to targetSize
     *
     * @param fragmentShaderFile File containing the fragment shader source for the executed shader program
     * @param context The context in which to operate and the target texture will be generated in
     * @param getNewSize Function that is called to determine the target size of the next iteration
     *        It must converge to a value equal or smaller than the target size given to 'run' when called recursive
     */
    GPUSurfaceCompactor(QString fragmentShaderFile, QSharedPointer<QOpenGLContext> context, QSize(&getNewSize)(QSize));

    /**
     * Destroys the GPUSurfaceCompactor.
     */
    ~GPUSurfaceCompactor() {}

    /**
     * Executes the set up operations by executing the shader.
     * Uses sourceTexture and targetSize set by their setter methods or previous calls to the run method with arguments.
     *
     * @return the compacted texture
     */
    virtual ::model::Surface::sptr run();

    /**
     * Executes the set up operations by executing the shader.
     *
     * @param targetSize the size to which the texture must at least be shrunken
     */
    virtual ::model::Surface::sptr run(QSize targetSize);

private:
    Q_DISABLE_COPY(GPUSurfaceCompactor);

    ::model::Surface::sptr compactTexture(const ::model::Surface &sourceTexture, QSize targetSize);

    QSize (&getNewSize)(QSize);
};

}  // namespace helper

#endif  // _GPUSURFACECOMPACTOR_H