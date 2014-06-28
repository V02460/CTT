


#if !defined(_FRAME_H)
#define _FRAME_H

#include "Histogram.h"
#include "HistogramType.h"
#include "FrameMetadata.h"

/**
 * Represents a frame (from a video), consisting of the actual image data as an an OpenGL Texture and corresponding Metadata.
 *
 */
class Frame {
public:
    /**
     * Creates a new frame from image data with corresponding metadata in a specific OppenGL context.
     *
     * @param context the OpenGL context in which the frame will be created
     * @param image image the image from which the frame will be generated
     * @param metadata metadata providing additional metadata about the frame
     */
    Frame(QOpenGLContext context, QImage image, FrameMetadata metadata);

    /**
     * Gets the metadata of the Frame.
     *
     * @return FrameMetadata the metadata of the Frame
     */
    FrameMetadata getMetadata();

    /**
     * Gets the texture containing the image data of the frame.
     *
     * @return QOpenGLTexture the texture containing the image data of the frame.
     */
    QOpenGLTexture getGLTexture();

    /**
     * creates a histogram of the submitted type from the frame and returns it.
     *
     * @param type specifies the histogram type
     * @return Histogram a histogram of the submitted type.
     */
    Histogram getHistogram(HistogramType type);

private:
    QOpenGLContext glContext; /**< An OpenGL context, from which the frame texture is accessible. */
    QOpenGLTexture glTexture; /**< The image data in an OpenGL texture */
    FrameMetadata *metadata; /**< Metadata containing additional information about the frame */
};

#endif  //_FRAME_H
