#include "LuminanceHistogram.h"

#include "OpenGLException.h"

namespace model {
namespace frame {
namespace histogram {

using ::exception::OpenGLException;

LuminanceHistogram::LuminanceHistogram(const Frame &frame) {
    init(frame);
}

Histogram::HistogramType LuminanceHistogram::getType() const {
    return HistogramType::Luminance;
}

QSharedPointer<QOpenGLShader> LuminanceHistogram::getHistogramGridFS()
{
    QSharedPointer<QOpenGLShader> shader(new QOpenGLShader(QOpenGLShader::Fragment));

    const char source[] = R"(
        uniform vec2 sourceSize;
        uniform vec2 targetSize;
        uniform sampler2D sourceImage;

        void main() {
            //texelFetch(image, texcrd, 0);
            gl_FragColor = vec4(gl_FragCoord.xy / targetSize.xy, 0.0, 0.0);
        }
    )";

    if (!shader->compileSourceCode(source)) {
        throw new OpenGLException("Fragment shader compilation failed. Log message: " + shader->log());
    }

    return shader;
}

}  // namespace histogram
}  // namespace frame
}  // namespace model