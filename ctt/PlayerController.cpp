#include "PlayerController.h"

namespace controller {

	using ::model::player::Player;

	PlayerController::PlayerController() {
		setPlayer(player);
	}

	void PlayerController::playPause() {
		player->togglePlayPause();
	}

	void PlayerController::nextFrame() {
		player->nextFrame();

	}

	void PlayerController::previousFrame() {
		player->previousFrame();
	}

	void PlayerController::currentFrameChanged(int frameNumber) {
		player->currentFrameNrChanged(frameNumber);
	}

	void PlayerController::setToDefaultFPS() {
		int defaultFPS = player->getDefaultFPS();
		player->setFPS(defaultFPS);
	}

	void PlayerController::setPlayer(Player::sptr player) {
		this->player = player;
	}

}  // namespace controller