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

#include "Surface.h"

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
class Histogram {
public:
    typedef QScopedPointer<Histogram> uptr;
    typedef QSharedPointer<Histogram> sptr;
	typedef QWeakPointer<Histogram> wptr;

	/** The size of a histogram. */
	static const unsigned int SIZE = 256;

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

    /**
    * Creates a new Histogram.
    */
    Histogram();

    /**
    * Initializes the histogram.
    *
    * @param frame Frame to calculate the histogram for
    */
    void init(const Frame &frame);

    /**
     * Provides the fragment shader used for creating the histogram grid.
     *
     * @return QSharedPointer<QOpenGLShader> histogram grid fragment shader
     */
    virtual QSharedPointer<QOpenGLShader> getHistogramGridFS() = 0;

private:
    /**
    * Converts every 16x16 block of the texture to a local normalized histogram.
    * Requires a valid OpenGL context.
    *
    * @param imageData Image data that will be used for the histogram grid calculation
    * @return Surface::sptr the generated histogram grid
    */
    Surface::sptr makeHistogramGrid(const Surface &imageData);

    /**
    * Calculates a given part of the histogram grid.
    * For all 16x16 cells an area in which valid data is contained must be given.
    *
    * @param image Original image data
    * @param target The image that is rendered into
    * @param area Area of the texture which should be calculated
    * @param validOffset Defines an area from the top left corner of every 16x16 block in which valid data is contained
    */
    //void calculateGridPart(const QOpenGLTexture &image,
    //                      QOpenGLFramebufferObject *target,
    //                       QRectF area,
    //                       QSize validOffset);

    /**
    * Extracts values for a single histogram from the grid of local histograms.
    *
    * @param histogramGrid Grid of local histograms
    * @return the histogram values
    */
    void requestValuesFromHistogramGrid(const Surface &histogramGrid) const;
};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_HISTOGRAM_H
