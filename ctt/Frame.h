#ifndef _FRAME_H
#define _FRAME_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QOpenGLTexture>
#include <QOpenGLContext>

#include "Histogram.h"
#include "HistogramType.h"
#include "FrameMetadata.h"
#include "Surface.h"

namespace model {
namespace frame {

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
     */
    Frame(QSharedPointer<QOpenGLContext> context, QImage image, FrameMetadata metadata);

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
     * creates a histogram of the submitted type from the frame and returns it.
     *
     * @param type specifies the histogram type
     * @return Histogram a histogram of the submitted type.
     */
    histogram::Histogram::sptr getHistogram(histogram::HistogramType type) const;

private:
    FrameMetadata::uptr metadata; /**< Metadata containing additional information about the frame */
};

}  // namespace frame
}  // namespace model

#endif  //_FRAME_H
