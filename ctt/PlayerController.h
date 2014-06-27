


#if !defined(_PLAYERCONTROLLER_H)
#define _PLAYERCONTROLLER_H

#include "Observer.h"
#include "Player.h"

class PlayerController : public Observer {
public:
	slot playPause();
	slot nextFrame();
	slot previousFrame();
	slot currentFrameChanged(int frameNumber);
	slot setToDefaultFPS();
	slot setPlayer(Player player);
};

#endif  //_PLAYERCONTROLLER_H
