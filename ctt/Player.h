


#if !defined(_PLAYER_H)
#define _PLAYER_H

#include "Savable.h"
#include "VideoScrubber.h"
#include "IntegerInterval.h"
#include "Memento.h"
#include <QTimer>

/**
 * A player organizes sychronized and complex access to multiple VideoScrubbers by telling them when to load which frames. It provides random access, asynchronous timer controlled playback with custom playback speed and looping.
 * The player will adapt to the shortest video and ignore all parts of the other videos exceeding this length.
 *
 */
class Player : public Saveable, public QObject {
	Q_OBJECT

public:
    /**
     * Creates a new player with an empty list of scrubbers and and initializes the playback speed with the submitted paramater.
     *
     * @param fps playback speed in frames per second
	 * @throws InvalidArgumentException if the submitted fps aren't greater than zero.
     */
    Player(double fps);

    /**
     * Starts playback with the currently set playback speed. Does nothing if the player is already playing. When the end of one of the videos is reached, the playback will automatically be paused.
     *
     */
    void play();

    /**
     * Pauses playback, but keeps the current frame. Does nothing if the player isn't currently playing.
     *
     */
    void pause();

    /**
     * Starts playback if the player is currently paused, else it pauses the playback.
     *
     */
    void togglePlayPause();

    /**
     * Jumps to the submitted framenumber and updates the scrubbers accordingly.
     *
     * @param frameNumber The player will jump to this framenumber
	 * @throws InvalidArgumentException if one of the scrubbers of the player don't have a frame with that number.
     */
    void jumpToFrameNr(unsigned int frameNumber);

    /**
     * Sets the playback speed in frames per second.
     *
     * @param fps the playback speed in fps
	 * @throws InvalidArgumentException if the submitted fps aren't greater than zero.
     */
    void setFPS(double fps);

    /**
     * Gets the currently set playback speed in frames per second.
     *
     * @return double the currently set playback speed in frames per second
     */
    double getFPS();

    /**
     * Gets a list of all the VideoScrubbers currently subscribed to this player.
     *
     * @return List<VideoSrubber> a list of all the VideoScrubebrs currently subscribed to this player.
     */
    List<VideoScrubber> getScrubbers();

    /**
     * Checks whether the player is currently playing.
     *
     * @return bool true only if the player is currently playing
     */
    bool isPlaying();

    /**
     * Adds a VideoScrubber to the list of VideoScrubbers controlled by the player at the end of that list.
     *
     * @param scrubber the scrubber that will be added to the list
     */
    void addScrubber(VideoScrubber scrubber);

    /**
     * Adds a VideoScrubber to the list of VideoScrubbers controlled by the player at the submitted position.
     *
     * @param scrubber the scrubber that will be added to the list
     * @param position the position of the list the player will be inserted at
     */
    void addScrubber(VideoScrubber scrubber, int position);

    /**
     * Removes the VideoScrubber with the submitted position from the list of VideoScrbbers controlled by the player.
     *
     * @param position the scrubber at this position will be removed.
	 * @throws InvalidArgumentException if there is no Scrubber at the submitted position
     */
    void removeScrubber(int position);

    /**
     * Removes the submitted VideoScrubber from the list of VideoScrubbers controlled by the player. If the submitted Scrubber isn't in the list, no changes willl be made.
     *
     * @param scrubber this scrubber will be removed
     */
    void removeScrubber(VideoScrubber scrubber);

    /**
     * Checks, whether the player controls a specific scrubber.
     *
     * @param scrubber for this scrubber will be checked whether the player controls it
     * @return bool true only if the scrubber is controlled by the player
     */
    bool controlsScrubber(VideoScrubber scrubber);

    /**
     * Returns the number of scrubbers controlled by this player.
     *
     * @return int the number of scrubbers controlled by this player
     */
	unsigned int scrubberCount();

    /**
     * Checks whether all of the scrubbers controlled by this player can provide the frame after the current frame.
     *
     * @return bool true only if all of the scrubbers controlled by this player can provide the frame after the current frame.
     */
    bool hasNextFrame();

	/**
	 * Checks whether all of the scrubbers controlled by this player can provide the frame before the current frame.
	 *
	 * @return bool true only if all of the scrubbers controlled by this player can provide the frame before the current frame.
	 */
    bool hasPreviousFrame();

    /**
     * Gets the length in frames per second of the shortest Video the scrubbers of this player use to get their frames from.
     *
     * @return int the length in frames per second of the shortest Video the scrubbers of this player use to get their frames from
     */
	unsigned int getVideoLength();

    /**
     * Gets the number of the current frame.
     *
     * @return int the number of the current frame
     */
	unsigned int getCurrentFrameNumber();

    /**
     * Tells the player to loop in the submitted interval. If the current frame isn't in the loop interval, the player will jump to the first frame in the loop interval.
     *
     * @param interval the interval in which the player will loop
	 * @throws InvalidArgumentException if the bounds of the interval aren't in the bounds of the videos.
     */
    void setLoop(IntegerInterval interval);

    /**
     * Gets the interval the player currently loops in. If the player doesn't loop currently, the last loop will be returned.
     *
     * @return IntegerInterval the interval the player currently loops in
     */
    IntegerInterval getLoop();

    /**
     * Checks whether the player is currently looping.
     *
     * @return bool true only if the player is currently looping.
     */
    bool isLooping();

    /**
     * The player stops looping. If the player isn't currently looping, nothing happens.
     *
     */
    void stopLooping();

    Memento getMemento();

    void restore(Memento memento);

    Savable* getDummy();

public slots:
    /**
     * Jumps to the frame after the current frame and updates the state of the scrubbers accordingly.
     *
     */
    void nextFrame();

    /**
     * Jumps to the frame before the current frame and updates the state of the scrubbers accordingly.
     *
     */
    void previousFrame();

signals:
    /**
     * Is emitted when the current frame changes.
     *
     * @param currentFrameNr the umber of the new current frame
     */
	void currentFrameNrChanged(unsigned int currentFrameNr);

private:
    int currentFrameNumber; /**< The number of the frame that was requested last */
	List<VideoScrubber> videoScrubbers; /**< The VideoScrubbers controlled by this player*/
    QTimer timer; /**< The timer controlling the playback speed */
    double fps; /**< The currently set playback speed in frames per second */
    bool looping; /**< Specifies whether the player is currently in a loop */
    bool playing; /**< Specifies whether the player is currently playing */
    IntegerInterval *loop; /**< Specifies the interval in which the player loops. */
};

#endif  //_PLAYER_H
