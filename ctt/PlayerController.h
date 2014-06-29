#if !defined(_PLAYERCONTROLLER_H)
#define _PLAYERCONTROLLER_H

#include "Observer.h"
#include "Player.h"

namespace controller {

/**
*	The PlayerController is notified when the state of the player changes and passes this information to all relevant components.
**/
class PlayerController : public Observer {
public slots:

	/**
	*	Is notified when the player function play or pause is requested and initiates playing or pausing a video.
	**/
	void playPause();

	/**
	*	Is notified when the player function nextFrame is requested and initiates returning the next frame of a video.
	**/
	void nextFrame();

	/**
	*	Is notified when the player function previousFrame is requested and initiates returning the next frame of a video.
	**/
	void previousFrame();

	/**
	*	Is notified when the player's current frame is requested to change and initiates changing to a specific frame of a video.
	*	@param frameNumber The number of the frame which is to be the current frame.
	**/
	void currentFrameChanged(int frameNumber);

	/**
	*	Is notified when the player is requested to set its FPS to the video's default and initiates setting the player's FPS to the video's default FPS.
	**/
	void setToDefaultFPS();

	/**
	*	Is notified when a new player is requested and initiates setting it.
	*	@param player The player which is to be set.
	**/
	void setPlayer(Player player);
};

}  // namespace controller

#endif  //_PLAYERCONTROLLER_H
