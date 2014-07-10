#include "HueHistogram.h"

namespace model {
namespace frame {
namespace histogram {

typedef QSharedPointer<QOpenGLShaderProgram> QOpenGLShaderProgram_sptr;

HueHistogram::HueHistogram(const Frame &frame) : Histogram(frame) {
}

Histogram::HistogramType HueHistogram::getType() const {
    return HistogramType::Blue;
}

QOpenGLShaderProgram_sptr HueHistogram::createHistogramGridShaderProgram() {
    auto program = QOpenGLShaderProgram_sptr(new QOpenGLShaderProgram());

    program->addShaderFromSourceCode(QOpenGLShader::Vertex, R"(
        attribute vec2 pos;
        varying vec2 oPos;
        varying vec2 texcrd;

        void main() {
            oPos = pos;

            gl_Position = vec4(pos, 0.0, 0.0);
        }
    )");

    program->addShaderFromSourceCode(QOpenGLShader::Fragment, R"(
        varying vec2 texcrd;
        uniform sampler2D image;

        void main() {
            gl_Color = texelFetch(image, texcrd, 0);
        }
    )");

    QOpenGLShader pixelShader(QOpenGLShader::Vertex);

    return program;
}

}  // namespace histogram
}  // namespace frame
}  // namespace model