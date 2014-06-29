#if !defined(_VIDEOSCRUBBER_H)
#define _VIDEOSCRUBBER_H

#include "Saveable.h"
#include "Observable.h"
#include "Frame.h"
#include "Video.h"
#include "VideoMetadata.h"
#include "Memento.h"
#include <QObject>

namespace model {
namespace player {

/**
 * A VideoScrubber is associated with a video and able to request frames from this video to save one of them internally.
 * It makes this frame available to other objects and notifies them via Qt's signal and slot mechanism when this frame is replaced.
 */
class VideoScrubber : public Saveable, public Observable, public QObject {
	Q_OBJECT
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
    VideoScrubber(Video video, unsigned int frameNumber);

    /**
     * Gets the metadata of the Video this VideoScrubber is associated with.
     *
     * @return VideoMetadata the metadata of the Video this VideoScrubber is associated with
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    VideoMetadata getVideoMetadata();

    /**
     * Gets the Video this VideoScrubber is associated with.
     *
     * @return Video the Video this VideoScrubber is associated with.
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    Video getVideo();

    /**
     * Gets the frame currently held by the scrubber.
     *
     * @return Frame the frame currently held by the scrubber
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    Frame getCurrentFrame();

	/**
	 * Checks whether the Scrubber is still waiting for the frame it requested last.
	 *
	 * @return bool true only if the Scrubber is still waiting for the frame it requested last.
	 * @throws IllegalStateException if the the method was called on a dummy
	 */
	bool isWaitingForFrame();

    Memento getMemento();

    void restore(Memento memento);

    Saveable* getDummy();

public slots:
    /**
     * The scrubber loads the frame with the provided frameNumber from the Video, saves it (overwriting the previously saved frame) and signals the change to connected slots.
     *
     * @param frameNumber the number of the frame wich will be requested from the video
     * @throws InvalidArgumentException if the video doesn't have a frame with the submitted number
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    void jumpToFrameNr(unsigned int frameNumber);

private:
    Video *video; /**< The scrubber gets frames and metadata from this video */
    Frame *currentFrame; /**< This is the frame currently held by the scrubber */
	bool waitingForFrame /**< This is true while Scrubber is still waiting for the frame it requested last*/
};

}  // namespace player
}  // namespace model


#endif  //_VIDEOSCRUBBER_H
