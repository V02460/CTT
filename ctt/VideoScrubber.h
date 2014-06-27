


#if !defined(_VIDEOSCRUBBER_H)
#define _VIDEOSCRUBBER_H

#include "Savable.h"
#include "Observable.h"
#include "Frame.h"
#include "Video.h"
#include "VideoMetadata.h"
#include "Memento.h"

/**
 * A VideoScrubber is associated with a video and able to request frames from this video to save one of them internally.
 * It makes this frame available to other objects and notifies them via Qt's signal and slot mechanism when this frame is replaced.
 */
class VideoScrubber : public Savable, public Observable {

public:
    /**
     * Creates a new VideoScrubber for the submitted video. Initially the Scrubber holds the first frame of the video.
     *
     * @param video the scrubber will use this video to get frames
	 * @throws InvalidArgumentException if the submitted video is invalid
     */
    VideoScrubber(Video video);

    /**
     * Creates a new VideoScrubber for the submitted video, initially holding the frame with the submitted number.
     *
     * @param video video the scrubber will use this video to get frames
     * @param frameNumber the scrubber will initially hold the frame with this number
     * @throws InvalidArgumentException if the submitted video is invalid or if it doesn't have a frame with the submitted number
     */
    VideoScrubber(Video video, int frameNumber);

    /**
     * Gets the metadata of the Video this VideoScrubber is associated with.
     *
     * @return VideoMetadata the metadata of the Video this VideoScrubber is associated with
     */
    VideoMetadata getVideoMetadata();

    /**
     * Gets the Video this VideoScrubber is associated with.
     *
     * @return Video the Video this VideoScrubber is associated with.
     */
    Video getVideo();

    /**
     * Gets the frame currently held by the scrubber.
     *
     * @return Frame the frame currently held by the scrubber
     */
    Frame getCurrentFrame();

    Memento getMemento();

    void restore(Memento memento);

    Savable* getDummy();

public slots:
    /**
     * The scrubber loads the frame with the provided frameNumber from the Video, saves it (overwriting the previously saved frame) and signals the change to connected slots.
     *
     * @param frameNumber the number of the frame wich will be requested from the video
     * @throws InvalidArgumentException if the video doesn't have a frame with the submitted number
     */
    void jumpToFrameNr(int frameNumber) = 0;

private:
    Video *video; /**< The scrubber gets frames and metadata from this video */
    Frame *currentFrame; /**< This is the frame currently held by the scrubber */
};

#endif  //_VIDEOSCRUBBER_H
