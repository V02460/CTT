#include "Histogram.h"

#include "Frame.h"
#include "MathHelper.h"
#include "GPUHelper.h"

#include "NotImplementedException.h"
#include "OpenGLException.h"

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
void Histogram::init(const Surface &frame) {
    Surface::sptr histogramGrid = makeHistogramGrid(frame);
    Surface::sptr histogramData = requestValuesFromHistogramGrid(*histogramGrid.data());
    histogramImage = renderHistogram(*histogramData.data());
}

// float Histogram::getValue(unsigned int i) const {
//     if (i >= histogramSize) {
//         throw new IllegalArgumentException("Out of bounds index " + QString::number(i) + ".");
//     }
// 
//     throw new NotImplementedException();
// }

Surface::sptr Histogram::getHistogramImage() const {
    return histogramImage;
}

Surface::sptr Histogram::makeHistogramGrid(const Surface &imageData) const {
    GPUHelper gpuHelper(getGridFSFilePath(), imageData.getContext());

    // scale output texture dimensions to the next bigger multiple of 16
    QSize targetSize = ceilTo(imageData.getSize(), 16);
    
    return gpuHelper.run(imageData, targetSize);
}

Surface::sptr Histogram::requestValuesFromHistogramGrid(const Surface &histogramGrid) const {
    GPUHelper gpuHelper(":/Shader/Histogram/histogramCompaction.fs", histogramGrid.getContext(), getCompactedSize);

    return gpuHelper.run(histogramGrid, QSize(16, 16));
}

Surface::sptr Histogram::renderHistogram(const Surface &histogramData) const {
    GPUHelper histogramDisplayer(":/Shader/Histogram/displayHistogram.fs", histogramData.getContext());

    return histogramDisplayer.run(histogramData, QSize(256, 128));
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