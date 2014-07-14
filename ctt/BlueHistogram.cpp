#include "BlueHistogram.h"

#include "QFile"

#include "OpenGLException.h"
#include "FileNotFoundException.h"

namespace model {
namespace frame {
namespace histogram {

using ::exception::OpenGLException;
using ::exception::FileNotFoundException;

BlueHistogram::BlueHistogram(const Frame &frame) {
    init(frame);
}

Histogram::HistogramType BlueHistogram::getType() const {
    return HistogramType::Blue;
}

QSharedPointer<QOpenGLShader> BlueHistogram::getHistogramGridFS()
{
    QSharedPointer<QOpenGLShader> shader(new QOpenGLShader(QOpenGLShader::Fragment));

    QFile sourceFile(":/Shader/Histogram/redHistogramGrid.fs");
    if (!sourceFile.exists()) {
        throw new FileNotFoundException("\"" + sourceFile.fileName() + "\" does not exist.");
    }

    QString source = sourceFile.readAll();

    if (!shader->compileSourceCode(source)) {
        throw new OpenGLException("Fragment shader compilation failed. Log message: " + shader->log());
    }

    return shader;
}

}  // namespace histogram
}  // namespace frame
}  // namespace model