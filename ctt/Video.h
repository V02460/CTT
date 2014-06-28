


#if !defined(_VIDEO_H)
#define _VIDEO_H

#include "Module.h"
#include "Frame.h"
#include "Memento.h"
#include "VideoMetadata.h"
#include "VideoFileType.h"
#include <QDir>

/**
 * Represents a video with all it's frames and metadata.
 *
 */
class Video : public Module {
public:
    /**
     * Gets the metadata of the Video which are valid for the whole video and not just specific frames
     *
     * @return VideoMetadata the metadata of the Video which are valid for the whole video and not just specific frames
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual VideoMetadata getMetadata() = 0;

    /**
     * Saves the Video to the submitted path in the filesystem
     *
     * @param path the path to where the video will be saved
     * @param fileType the file type in which the video will be saved
     * @throws IOException if it's not possible to save the video to the submitted path
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    void save(QDir path, VideoFileType fileType);

    /**
     * Gets the frame with the submitted number scaled to the submitted resolution.
     * Rescaling will use bicubic interpolation.
     *
     * @param frameNumber the number of the frame which will be returned
     * @param x the width of the frame which will be returned
     * @param y the height of the frame which will be returned
     * @return Frame the scaled Frame
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual Frame getScaledFrame(unsigned int frameNumber, unsigned int x, unsigned int y);

    virtual Frame getFrame(unsigned int frameNumber);

    virtual Memento getMemento();

    virtual void restore(Memento memento);

    virtual Saveable* getDummy();
private:
    VideoMetadata *metadata; /**< the metadata of the Video which are valid for the whole video and not just specific frames */
};

#endif  //_VIDEO_H
