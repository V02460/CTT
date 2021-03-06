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
	static const unsigned int kSize = 256;

    /**
     * Labels for the channels histograms describe the intensity distribution of.
	 *
	 * This enum must be parallel to the HISTOGRAM_TYPE_STRINGS list.
     */
    enum HistogramType {
        Red,
        Green,
        Blue,
        Hue,
        Saturation,
        Luminance
    };

	/** String representation of the red histogram type. */
	static const QString kRedStr;
	/** String representation of the green histogram type. */
	static const QString kGreenStr;
	/** String representation of the blue histogram type. */
	static const QString kBlueStr;
	/** String representation of the hue histogram type. */
    static const QString kHueStr;
	/** String representation of the saturation histogram type. */
    static const QString kSaturationStr;
	/** String representation of the luminance histogram type. */
	static const QString kLuminanceStr;

	/**
	 * A list if String representations of Histogram Types.
	 *
	 * This list must be parallel to the HistogramType enum.
	 */
	static const QList<QString> HISTOGRAM_TYPE_STRINGS;

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

	QVector<float> getValues() const;

    Surface::sptr getHistogramImage(QSize dimensions) const;

    /**
     * Gets the type of the histogram, specifying the type of variable the histogram describes the distribution of. 
     *
     * @return HistogramType the type of the histogram
     */
    virtual HistogramType getType() const = 0;

	/**
	 * Returns the histogram type represented by the string.
	 *
	 * @param string The string representation of the type to return.
	 * @return The histogram type represented by the string.
	 */
	static const HistogramType stringToType(QString string);

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
    void init(Surface::sptr frame);

    /**
     * Provides the path to the fragment shader used for creating the histogram grid.
     *
     * @return QString fragment shader path
     */
    virtual QString getGridFSFilePath() const = 0;

private:
    /**
    * Converts every 16x16 block of the texture to a local normalized histogram.
    * Requires a valid OpenGL context.
    *
    * @param imageData Image data that will be used for the histogram grid calculation
    * @return Surface::sptr the generated histogram grid
    */
    Surface::sptr makeHistogramGrid(Surface::sptr imageData) const;

    /**
    * Extracts values for a single histogram from the grid of local histograms.
    *
    * @param histogramGrid Grid of local histograms
    * @return the histogram values
    */
    Surface::sptr requestValuesFromHistogramGrid(Surface::sptr imageData) const;

    Surface::sptr renderHistogram(Surface::sptr histogramData, QSize targetSize) const;

    /**
     * The values stored in a 16x16px Surface (on GPU).
     */
    Surface::sptr histogramData;

    /**
     * The values of the histogram stored as float array (on CPU).
     */
    mutable QVector<float> values;

	void calculateValues() const;
    

};

}  // namespace histogram
}  // namespace frame
}  // namespace model

#endif  //_HISTOGRAM_H
