#ifndef _HISTOGRAM_H
#define _HISTOGRAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QVector>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>

//#include "Frame.h"
namespace model {
namespace frame {
    class Frame;
}}

namespace model {
namespace frame {
namespace histogram {

/**
 * A Histogram with 256 values describing the intensity distribution of a channel in a frame.
 */
class Histogram : protected QOpenGLFunctions {
public:
    typedef QScopedPointer<Histogram> uptr;
    typedef QSharedPointer<Histogram> sptr;
    typedef QWeakPointer<Histogram> wptr;

    /**
     * Labels for the channels histograms describe the intensity distribution of.
     */
    enum HistogramType {
        Red,
        Green,
        Blue,
        Luminance,
        Hue,
        Saturation
    };

    /**
     * Creates a new Histogram from a given frame.
     * Results are calculated asynchronously on the GPU
     * When requested immediately the thread blocks until they have been calculated.
     *
     * @param frame Frame from which to calculate the Histogram for
     */
    explicit Histogram(const Frame &frame);

    /**
     * Destroys the Histogram.
     */
    virtual ~Histogram() = 0 {};

    /**
     * Gets the value for the entry with the number i.
     *
     * @param i the value of this entry will be returned
     * @return float the value for the entry with the number i
     * @throws InvalidArgumentException if i > 255
     */
    virtual float getValue(unsigned int i) const;

    /**
     * Gets the type of the histogram, specifying the type of variable the histogram describes the distribution of. 
     *
     * @return HistogramType the type of the histogram
     */
    virtual HistogramType getType() const = 0;

protected:
    virtual QSharedPointer<QOpenGLShaderProgram> createHistogramGridShaderProgram() = 0;

    const unsigned int histogramSize = 256;

private:
    QSharedPointer<QOpenGLShaderProgram> createCompactionShaderProgram();

    /**
    * Converts every 16x16 block of the texture to a local normalized histogram.
    * Requires a valid OpenGL context.
    *
    * @param image Image that will be used for the histogram grid calculation
    * @return QSharedPointer<QOpenGLTexture> the generated histogram grid
    */
    QSharedPointer<QOpenGLFramebufferObject> makeHistogramGrid(const QOpenGLTexture &inTexture);

    /**
    * Calculates a given part of the histogram grid.
    * For all 16x16 cells an area in which valid data is contained must be given.
    *
    * @param image Original image data
    * @param target The image that is rendered into
    * @param area Area of the texture which should be calculated
    * @param validOffset Defines an area from the top left corner of every 16x16 block in which valid data is contained
    */
    void calculateGridPart(const QOpenGLTexture &image,
                           QOpenGLFramebufferObject *target,
                           QRect area,
                           QSize validOffset);

    /**
    * Extracts values for a single histogram from the grid of local histograms.
    *
    * @param histogramGrid Grid of local histograms
    * @return the histogram values
    */
    void requestValuesFromHistogramGrid(QOpenGLFramebufferObject *histogramGrid);

    /**
    * Collapses square groups of four histograms to a new histogram.
    *
    * @param histogramGridId Texture handle of the source grid
    * @param sourceGridSize Dimension of the source grid texture. Must be multiple of 16.
    * @param target The target that will hold the compacted grid
    * @return bool true if a compaction has taken place
    */
    bool compactHistogramGrid(GLuint histogramGridId, QSize sourceGridSize, QOpenGLFramebufferObject *target);

    void compactHistogramGridPartial();
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_HISTOGRAM_H
