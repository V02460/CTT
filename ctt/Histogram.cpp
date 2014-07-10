#include "Histogram.h"

#include "Frame.h"

#include "IllegalArgumentException.h"

namespace model {
namespace frame {
namespace histogram {

using ::exception::IllegalArgumentException;

typedef QSharedPointer<QOpenGLShaderProgram> QOpenGLShaderProgram_sptr;
typedef QSharedPointer<QOpenGLTexture> QOpenGLTexture_sptr;
typedef QScopedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_uptr;
typedef QSharedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_sptr;

Histogram::Histogram(const Frame &frame) {

}

float Histogram::getValue(unsigned int i) const {
    if (i >= histogramSize) {
        throw new IllegalArgumentException("Out of bounds index " + QString(i) + ".");
    }

    return 0.0; // TODO
}

QOpenGLFramebufferObject_sptr Histogram::makeHistogramGrid(const QOpenGLTexture &image) {

}

QOpenGLShaderProgram_sptr Histogram::createCompactionShaderProgram() {

}
void Histogram::requestValuesFromHistogramGrid(QOpenGLFramebufferObject *histogramGrid) {

}

void Histogram::compactHistogramGridPartial() {

}

bool Histogram::compactHistogramGrid(GLuint histogramGridId, QSize sourceGridSize, QOpenGLFramebufferObject *target) {
}


}  // namespace histogram
}  // namespace frame
}  // namespace model