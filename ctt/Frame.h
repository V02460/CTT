#ifndef _FRAME_H
#define _FRAME_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QOpenGLTexture>
#include <QOpenGLContext>

#include "FrameMetadata.h"
#include "Surface.h"
#include "Histogram.h"

#include "IllegalArgumentException.h"

namespace model {
namespace frame {

using histogram::Histogram;

/**
 * Represents a frame, consisting of image data as an an OpenGL Texture and corresponding Metadata.
 *
 */
class Frame: public Surface {
public:
    typedef QScopedPointer<Frame> uptr;
    typedef QSharedPointer<Frame> sptr;
    typedef QWeakPointer<Frame> wptr;

    /**
     * Creates a new Frame from image data with corresponding metadata in a specific OpenGL context.
     *
     * @param context the OpenGL context in which the frame will be created
     * @param image image the image from which the frame will be generated
     * @param metadata metadata providing additional metadata about the frame
	 * @throws IllegalArgumentException if the size of the submitted image doesn't fit the size specified in the 
	 *	submitted metadata.
     */
    Frame(QSharedPointer<QOpenGLContext> context, QImage image, FrameMetadata metadata);

    /**
    * Creates a new Frame from image data in a specific OpenGL context.
    * Automatically creates a Metadata object containing the size of the image
    *
    * @param context the OpenGL context in which the frame will be created
    * @param image image the image from which the frame will be generated
    * @throws IllegalArgumentException if the size of the submitted image zero or negative area
    */
    Frame(QSharedPointer<QOpenGLContext> context, QImage image);

    /**
     * Creates a new empty Frame with corresponding metadata in a specific OpenGL context.
     *
     * @param context the OpenGL context in which the frame will be created
     * @param metadata metadata providing additional metadata about the frame
     */
    Frame(QSharedPointer<QOpenGLContext> context, FrameMetadata metadata);

    /**
     * Gets the metadata of the Frame.
     *
     * @return FrameMetadata the metadata of the Frame
     */
    FrameMetadata getMetadata() const;

    /**
     * Creates a histogram of the submitted type from the frame and returns it.
     *
     * @param frame the frame used for the histogram creation
     * @param type specifies the histogram type
     * @return Histogram a histogram of the submitted type.
     * @throws IllegalArgumentException on unsupported type
     */
    static Histogram::sptr getHistogram(Frame::sptr frame, Histogram::HistogramType type);

//TODO: this is a dangerous constructor when used without care
//protected:
    /**
     * Creates a Frame from a Surface by incorporating it. Cripples surface.
     *
     * @param surface The Surface Frame takes its attributes from.
     */
    Frame(Surface::sptr surface, FrameMetadata metadata);

private:
    Q_DISABLE_COPY(Frame)

    FrameMetadata metadata; /**< Metadata containing additional information about the frame */
};

}  // namespace frame
}  // namespace model

#endif  //_FRAME_H
