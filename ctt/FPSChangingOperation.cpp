#include "FPSChangingOperation.h"
#include "Player.h"

namespace controller {
namespace operation {

	using ::model::player::Player;

	FPSChangingOperation::FPSChangingOperation(double newFPS, Player::sptr player) : newFPS(newFPS), oldFPS(player->getFPS()), 
		player(player) {

	}

	void FPSChangingOperation::doOperation() {
		player->setFPS(newFPS);
	}

	void FPSChangingOperation::undoOperation() {
		player->setFPS(oldFPS);
	}

}  // namespace operation
}  // namespace controller