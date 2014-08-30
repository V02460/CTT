#include "PlayerController.h"
#include "NotImplementedException.h"

#include "NotImplementedException.h"

namespace controller {

	using ::model::player::Player;
	using ::exception::NotImplementedException;

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
		player->jumpToFrameNr(static_cast<unsigned int>(frameNumber));
	}

	void PlayerController::setToDefaultFPS() {
		int defaultFPS = player->getDefaultFPS();
		player->setFPS(defaultFPS);
	}

	void PlayerController::setPlayer(Player::sptr player) {
		this->player = player;
	}

	void PlayerController::setFPS(int fps) {
		//TODO implement
	}

	void PlayerController::update() {
		throw new NotImplementedException();
	}

}  // namespace controller