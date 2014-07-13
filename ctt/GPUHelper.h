#ifndef _GPUHELPER_H
#define _GPUHELPER_H

#include <QSharedPointer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QSize>
#include <QOpenGLFunctions>

#include "Surface.h"

#include "OpenGLException.h"

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
     * Destroys the GPUHelper.
     */
    ~GPUHelper() {}

    /**
     * Returns an instance of GPUHelper.
     *
     * @return GPUHelper::sptr instance of GPUHelper
     */
    static GPUHelper::sptr instance();

    /**
     * Returns a default vertex shader which can be used in conjunction with applyShader().
     *
     * @return QSharedPointer<QOpenGLShader> default shader
     */
    static QOpenGLShader_sptr getDefaultFlatVS();

    /**
     * Runs a shader program and stores its result in target.
     *
     * @param target Surface that is rendered into
     * @param program Shader program to call
     * @throws OpenGLException when framebuffer object or shader program could not be bound
     */
    void runShader(::model::Surface *target, QOpenGLShaderProgram *program);

    /**
    * Repeatedly collapses sourceTexture to a smaller size until it reaches a target size.
    *
    * @param sourceTexture Texture handle of the source grid
    * @param compationProgram Shader program which is applied at every iteration
    * @param getNewSize Function that is called to determine the target size of the next iteration
    *        It must converge to a value equal or smaller than targetSize when called recursive
    * @param targetSize This method returns when it generates a texture with dimensions smaller or equal to targetSize
    * @param context The context in which the target texture will be created
    * @return QSharedPointer<QOpenGLFramebufferObject> The target that will hold the compacted grid
    */
    ::model::Surface::sptr compactTexture(const ::model::Surface &sourceTexture,
                                 QOpenGLShaderProgram *compactionProgram,
                                 QSize(&getNewSize)(QSize),
                                 QSize targetSize);

private:
    GPUHelper();

    static GPUHelper::sptr helperInstance;
};

}  // namespace helper

#endif  // _GPUHELPER_H