#ifndef _PLAYER_H
#define _PLAYER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QTimer>
#include <QObject>

#include "Saveable.h"
#include "VideoScrubber.h"
#include "UIntegerInterval.h"
#include "Memento.h"

namespace model {
namespace player {

/**
 * A player organizes synchronized and complex access to multiple VideoScrubbers by telling them when to load which
 * frames. It provides random access, asynchronous timer controlled playback with custom playback speed and looping.
 * The player will adapt to the shortest video and ignore all parts of the other videos exceeding this length.
 *
 */
class Player : public QObject, public ::model::saveable::Saveable, public Observable {
    Q_OBJECT

public:
    typedef QScopedPointer<Player> uptr;
    typedef QSharedPointer<Player> sptr;
    typedef QWeakPointer<Player> wptr;

    /**
    * Creates a new player with an empty list of scrubbers and and initializes the playback speed with the submitted
    * parameter.
    *
    * @param fps playback speed in frames per second
    * @throws InvalidArgumentException if the submitted fps aren't greater than zero.
    */
    explicit Player(double fps);

    /**
     * Destroys the Player.
     */
     ~Player();

    /**
     * Starts playback with the currently set playback speed. Does nothing if the player is already playing. When the
     * end of one of the videos is reached, the playback will automatically be paused.
	 * If the player has already reached the end of one of its videos and play is called, the player will start its 
	 * Videos from the beginning.
     *
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void play();

    /**
     * Pauses playback, but keeps the current frame. Does nothing if the player isn't currently playing.
     *
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void pause();

    /**
     * Starts playback if the player is currently paused, else it pauses the playback.
     *
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void togglePlayPause();

    /**
     * Jumps to the submitted frame number and updates the scrubbers accordingly.
	 * Doesn't do anything if the loading if the previous frame isn't complete yet.
     *
     * @param frameNumber The player will jump to this frame number
     * @throws InvalidArgumentException if one of the scrubbers of the player don't have a frame with that number.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void jumpToFrameNr(unsigned int frameNumber);

    /**
     * Sets the playback speed in frames per second.
     *
     * @param fps the playback speed in fps
     * @throws InvalidArgumentException if the submitted fps aren't greater than zero.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void setFPS(double fps);

    /**
     * Gets the currently set playback speed in frames per second.
     *
     * @return double the currently set playback speed in frames per second
     * @throws IllegalStateException if the the method was called on a dummy
     */
    double getFPS() const;

    /**
     * Gets a list of all the VideoScrubbers currently subscribed to this player.
     *
     * @return QList<::model::player::VideoScrubber::wptr> a list of all the VideoScrubebrs currently subscribed to this
     *     player.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    QList<::model::player::VideoScrubber::sptr> getScrubbers() const;

    /**
     * Checks whether the player is currently playing.
     *
     * @return bool true only if the player is currently playing
     * @throws IllegalStateException if the the method was called on a dummy
     */
    bool isPlaying() const;

    /**
     * Adds a VideoScrubber to the list of VideoScrubbers controlled by the player at the end of that list.
     *
     * @param scrubber the scrubber that will be added to the list
     * @throws IllegalStateException if the the method was called on a dummy
	 * @throws IllegalArgumentException if the submitted scrubber is a dummy
     */
    void addScrubber(::model::player::VideoScrubber::sptr scrubber);

    /**
     * Adds a VideoScrubber to the list of VideoScrubbers controlled by the player at the submitted position.
     *
     * @param scrubber the scrubber that will be added to the list
     * @param position the position of the list the player will be inserted at
     * @throws IllegalStateException if the the method was called on a dummy
	 * @throws IllegalArgumentException if the submitted scrubber is a dummy
	 * @throws IllegalArgumentException if the submitted position is too high
     */
    void addScrubber(::model::player::VideoScrubber::sptr scrubber, unsigned int position);

    /**
     * Removes the VideoScrubber with the submitted position from the list of VideoScrbbers controlled by the player.
     *
     * @param position the scrubber at this position will be removed.
     * @throws IllegalArgumentException if there is no Scrubber at the submitted position
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void removeScrubber(unsigned int position);

    /**
     * Removes the submitted VideoScrubber from the list of VideoScrubbers controlled by the player.
     *
     * @param scrubber this scrubber will be removed
     * @throws IllegalStateException if the the method was called on a dummy
	 * @throws IllegalArgumentException if the submitted scrubber isn't in the list of VideoScrubbers controlled by the 
	 *		player
     */
    void removeScrubber(const ::model::player::VideoScrubber &scrubber);

    /**
     * Checks, whether the player controls a specific scrubber.
     *
     * @param scrubber for this scrubber will be checked whether the player controls it
     * @return bool true only if the scrubber is controlled by the player
     * @throws IllegalStateException if the the method was called on a dummy
     */
    bool controlsScrubber(const ::model::player::VideoScrubber &scrubber) const;

    /**
     * Returns the number of scrubbers controlled by this player.
     *
     * @return int the number of scrubbers controlled by this player
     * @throws IllegalStateException if the the method was called on a dummy
     */
    unsigned int scrubberCount() const;

    /**
     * Checks whether all of the scrubbers controlled by this player can provide the frame after the current frame.
     *
     * @return bool true only if all of the scrubbers controlled by this player can provide the frame after the current
     *     frame.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    bool hasNextFrame() const;

    /**
     * Checks whether all of the scrubbers controlled by this player can provide the frame before the current frame.
     *
     * @return bool true only if all of the scrubbers controlled by this player can provide the frame before the current
     *     frame.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    bool hasPreviousFrame() const;

    /**
     * Gets the length in frames per second of the shortest Video the scrubbers of this player use to get their frames
     * from. Returns 0 if the player has no scrubbers.
     *
     * @return int the length in frames per second of the shortest Video the scrubbers of this player use to get their
     *     frames from
     * @throws IllegalStateException if the the method was called on a dummy
     */
    unsigned int getVideoLength() const;

    /**
     * Gets the number of the current frame.
     *
     * @return int the number of the current frame
     * @throws IllegalStateException if the the method was called on a dummy
     */
    unsigned int getCurrentFrameNumber() const;

    /**
     * Tells the player to loop in the submitted interval. If the current frame isn't in the loop interval, the player
     * will jump to the first frame in the loop interval.
     *
     * @param interval the interval in which the player will loop
	 * @throws IllegalArgumentException if the submitted interval is a dummy.
     * @throws IllegalArgumentException if the bounds of the interval aren't in the bounds of the videos.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void setLoop(UIntegerInterval interval);

    /**
     * Gets the interval the player currently loops in. If the player doesn't loop currently, the last loop will be
     * returned.
     *
     * @return IntegerInterval the interval the player currently loops in
     * @throws IllegalStateException if the the method was called on a dummy
     */
    UIntegerInterval getLoop() const;

    /**
     * Checks whether the player is currently looping.
     *
     * @return bool true only if the player is currently looping.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    bool isLooping() const;

    /**
     * The player stops looping. If the player isn't currently looping, nothing happens.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void stopLooping();

    virtual ::model::saveable::Memento getMemento() const;
    virtual void restore(::model::saveable::Memento memento);
	static ::model::saveable::Saveable::sptr getDummy();
    static Saveable::SaveableType getSaveableType();

public slots:
    /**
     * Jumps to the frame after the current frame and updates the state of the scrubbers accordingly.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void nextFrame();

    /**
     * Jumps to the frame before the current frame and updates the state of the scrubbers accordingly.
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void previousFrame();

signals:
    /**
     * Is emitted when the current frame changes.
     *
     * @param currentFrameNr the umber of the new current frame
     * @throws IllegalStateException if the the method was called on a dummy
     */
    void currentFrameNrChanged(unsigned int currentFrameNr);

private:
	Q_DISABLE_COPY(Player)
	/**
	* Creates a dummy Player.
	*/
	Player();

	const static QString fpsStringId; /**< The Id the scrubber uses to save its fps in a memento */
	const static QString scrubbersStringId; /**< The Id the scrubber uses to save its scrubbers in a memento */
	const static QString numberOfScrubbersStringId; /**< The Id the scrubber uses to save its number of scrubbers in a memento */

    unsigned int currentFrameNumber; /**< The number of the frame that was requested last */
    QList<::model::player::VideoScrubber::sptr> videoScrubbers; /**< The VideoScrubbers controlled by this player*/
    QTimer timer; /**< The timer controlling the playback speed */
    double fps; /**< The currently set playback speed in frames per second */
    bool looping; /**< Specifies whether the player is currently in a loop */
    bool playing; /**< Specifies whether the player is currently playing */
    UIntegerInterval loop; /**< Specifies the interval in which the player loops. */
};

}  // namespace player
}  // namespace model

#endif  //_PLAYER_H
