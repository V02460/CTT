#include "Histogram.h"

#include "Frame.h"
#include "MathHelper.h"
#include "GPUHelper.h"

#include "NotImplementedException.h"

namespace model {
namespace frame {
namespace histogram {

using ::helper::GPUHelper;

using ::exception::IllegalArgumentException;
using ::exception::OpenGLException;
using ::exception::NotImplementedException;

using helper::ceilTo;
using helper::floorTo;

typedef QSharedPointer<QOpenGLShaderProgram> QOpenGLShaderProgram_sptr;
typedef QSharedPointer<QOpenGLTexture> QOpenGLTexture_sptr;
typedef QScopedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_uptr;
typedef QSharedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_sptr;

static QSize getCompactedSize(QSize currentSize);

Histogram::Histogram() {
}

const QString Histogram::RED = "red";
const QString Histogram::GREEN = "green";
const QString Histogram::BLUE = "blue";
const QString Histogram::LUMINANCE = "luminance";
const QString Histogram::HUE = "hue";
const QString Histogram::SATURATION = "saturation";

const QList<QString> Histogram::HISTOGRAM_TYPE_STRINGS = QList<QString>()
<< RED
<< GREEN
<< BLUE
<< LUMINANCE
<< HUE
<< SATURATION;

const Histogram::HistogramType Histogram::stringToType(QString string) {
	for (int i = 0; i < HISTOGRAM_TYPE_STRINGS.length(); i++) {
		if (string == HISTOGRAM_TYPE_STRINGS[i]) {
			return static_cast<HistogramType>(i);
		}
	}
	throw new IllegalArgumentException(string + " is not a histogram type.");
}

/**
* A list if String representations of Histogram Types.
*
* This list must be parallel to the HistogramType enum.
*/
static const QList<QString> HISTOGRAM_TYPE_STRINGS;

void Histogram::init(const Frame &frame) {
    Surface::sptr histogramGrid = makeHistogramGrid(frame);
    requestValuesFromHistogramGrid(*histogramGrid.data());
}

float Histogram::getValue(unsigned int i) const {
    if (i >= SIZE) {
        throw new IllegalArgumentException("Out of bounds index " + QString::number(i));
    }

    throw new NotImplementedException();
}

Surface::sptr Histogram::makeHistogramGrid(const Surface &imageData) {
    QSize sourceSize = imageData.getSize();

    // scale output texture dimensions to the next bigger multiple of 16
    QSize targetSize = ceilTo(sourceSize, 16);

    //QSize sizeDelta = targetSize - sourceSize;

    QOpenGLShaderProgram program;
    if (!program.addShader(GPUHelper::getDefaultFlatVS().data())) {
        throw new OpenGLException("Adding of vertex shader failed. Log message: " + program.log());
    }

    if (!program.addShader(getHistogramGridFS().data())) {
        throw new OpenGLException("Adding of fragment shader failed. Log message: " + program.log());
    }
    
    if (!program.link()) { // TODO: cache program
        throw new OpenGLException("Linking of shader program failed. Log message: " + program.log());
    }

    program.setUniformValue("sourceSize", sourceSize);
    program.setUniformValue("targetSize", targetSize);
    program.setUniformValue("sourceImage", imageData.getTextureHandle());

    return imageData.applyShader(&program, targetSize);
}

void Histogram::requestValuesFromHistogramGrid(const Surface &histogramGrid) const {

    QOpenGLShaderProgram program;

    if (!program.addShader(GPUHelper::getDefaultFlatVS().data())) {
        throw new OpenGLException("Adding of vertex shader failed. Log message: " + program.log());
    }

    const char fragmentSource[] = R"(
        uniform vec2 sourceSize;
        uniform vec2 targetSize;
        uniform sampler2D sourceImage;

        void main() {
            //texelFetch(image, texcrd, 0);
            gl_FragColor = vec4(gl_FragCoord.xy / targetSize.xy, 0.0, 0.0);
        }
    )";

    if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource)) {
        throw new OpenGLException("Adding or compilation of fragment shader failed. Log message: " + program.log());
    }

    if (!program.link()) { // TODO: cache program
        throw new OpenGLException("Linking of shader program failed. Log message: " + program.log());
    }

    GPUHelper::instance()->compactTexture(histogramGrid, &program, getCompactedSize, QSize(16, 16));

    // TODO: get values from calculated histogram
}

/**
 * Returns the texture dimensions for the compaction logic.
 * 4x 16x16 blocks must be compacted to one.
 * So we get the next biggest multiple of 32 and halve it
 *
 * @param currentSize Initial dimensions
 * @return QSize New dimensions
 */
static QSize getCompactedSize(QSize currentSize) {
    return QSize(((currentSize.width() + 31) / 32) * 16,
                 ((currentSize.height() + 31 ) / 32) * 16);
}

}  // namespace histogram
}  // namespace frame
}  // namespace model