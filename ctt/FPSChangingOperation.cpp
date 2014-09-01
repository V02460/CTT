#include "FPSChangingOperation.h"
#include "Player.h"

namespace controller {
namespace operation {

	using ::model::player::Player;

	FPSChangingOperation::FPSChangingOperation(double newFPS, Player::sptr player) : newFPS(newFPS),
																					 player(player),
																					 memento(player->getMemento()) {}

	void FPSChangingOperation::doOperation() {
		player->setFPS(newFPS);
	}

	void FPSChangingOperation::undoOperation() {
		player->restore(memento);
		player->changed();
	}

}  // namespace operation
}  // namespace controller