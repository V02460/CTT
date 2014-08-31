#include "Histogram.h"

#include "Frame.h"
#include "MathHelper.h"
#include "GPUSurfaceShader.h"
#include "GPUSurfaceCompactor.h"

#include "NotImplementedException.h"
#include "OpenGLException.h"

namespace model {
namespace frame {
namespace histogram {

using ::helper::GPUSurfaceShader;
using ::helper::GPUSurfaceCompactor;
using ::helper::ceilTo;
using ::helper::floorTo;
using ::exception::IllegalArgumentException;
using ::exception::OpenGLException;
using ::exception::NotImplementedException;

typedef QSharedPointer<QOpenGLShaderProgram> QOpenGLShaderProgram_sptr;
typedef QSharedPointer<QOpenGLTexture> QOpenGLTexture_sptr;
typedef QScopedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_uptr;
typedef QSharedPointer<QOpenGLFramebufferObject> QOpenGLFramebufferObject_sptr;

static QSize getCompactedSize(QSize currentSize);

const QString Histogram::kRedStr = "red";
const QString Histogram::kGreenStr = "green";
const QString Histogram::kBlueStr = "blue";
const QString Histogram::kHueStr = "hue";
const QString Histogram::kSaturationStr = "saturation";
const QString Histogram::kLuminanceStr = "luminance";

const QList<QString> Histogram::HISTOGRAM_TYPE_STRINGS = 
    QList<QString>() << kRedStr
                     << kGreenStr
                     << kBlueStr
                     << kHueStr
                     << kSaturationStr
                     << kLuminanceStr;

static const QList<QString> HISTOGRAM_TYPE_STRINGS;

Histogram::Histogram() {
}

float Histogram::getValue(unsigned int idx) const {
    if (idx >= kSize) {
        throw new IllegalArgumentException("Out of bounds index " + QString::number(idx) + ".");
    }

    if (values.isEmpty()) {
        values.resize(kSize);

        // TODO: use PBO to prevent GPU pipeline flush
        QByteArray rawValues = histogramData->getRawRGBA();

        for (unsigned int i = 0; i < kSize; i++) {

            // decode the floats stored in the RGBA8888 format
            char r = rawValues[4 * i    ];
            char g = rawValues[4 * i + 1];
            char b = rawValues[4 * i + 2];
            char a = rawValues[4 * i + 3];
                
            values[i] = reinterpret_cast<unsigned char&>(r) / 255.f
                      + reinterpret_cast<unsigned char&>(g) / 65025.f
                      + reinterpret_cast<unsigned char&>(b) / 16581375.f
                      + reinterpret_cast<unsigned char&>(a) / 4228250625.f;
        }
    }

    return values[idx];
}

Surface::sptr Histogram::getHistogramImage(QSize dimensions) const {
    return renderHistogram(histogramData, dimensions);
}

const Histogram::HistogramType Histogram::stringToType(QString string) {
	for (int i = 0; i < HISTOGRAM_TYPE_STRINGS.length(); i++) {
		if (string == HISTOGRAM_TYPE_STRINGS[i]) {
			return static_cast<HistogramType>(i);
		}
	}

	throw new IllegalArgumentException(string + " is not a histogram type.");
}

void Histogram::init(Surface::sptr frame) {
    Surface::sptr histogramGrid = makeHistogramGrid(frame);
    histogramData = requestValuesFromHistogramGrid(histogramGrid);
}

Surface::sptr Histogram::makeHistogramGrid(Surface::sptr imageData) const {
    GPUSurfaceShader gpuHelper(getGridFSFilePath(), imageData);

    // scale output texture dimensions to the next bigger multiple of 16
    QSize targetSize = ceilTo(imageData->getSize(), 16);

    return gpuHelper.run(targetSize);
    }

Surface::sptr Histogram::requestValuesFromHistogramGrid(Surface::sptr histogramGrid) const {
    GPUSurfaceCompactor gpuHelper(":/Shader/Histogram/histogramCompaction.fs",
                                  histogramGrid,
                                  getCompactedSize);
    
    return gpuHelper.run(QSize(16, 16));
    }

Surface::sptr Histogram::renderHistogram(Surface::sptr histogramData, QSize targetSize) const {
    GPUSurfaceShader histogramDisplayer(":/Shader/Histogram/displayHistogram.fs", histogramData);

    return histogramDisplayer.run(targetSize);
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