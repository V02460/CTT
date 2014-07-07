#include "PlayerFunctions.h"

namespace view {

void PlayerFunctions::subscribe(::controller::PlayerController::sptr observer);

void PlayerFunctions::unsubscribe(const ::controller::PlayerController &observer);

}  // namespace view