#include "PlayerController.h"
#include "Operation.h"
#include "OperationList.h"
#include "FPSChangingOperation.h"

namespace controller {

	using ::model::player::Player;
	using ::controller::operation::Operation;
	using ::controller::operation::OperationList;
	using ::controller::operation::FPSChangingOperation;

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
		double defaultFPS = player->getDefaultFPS();
		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new FPSChangingOperation(defaultFPS, player)));
	}

	void PlayerController::setFPS(double fps) {
		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new FPSChangingOperation(fps, player)));
	}

	void PlayerController::setPlayer(Player::sptr player) {
		this->player = player;
	}

}  // namespace controller