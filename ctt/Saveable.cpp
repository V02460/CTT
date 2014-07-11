#include "Saveable.h"

namespace model {
namespace saveable {

bool Saveable::isDummy() const {
	return isDummyFlag;
}

Saveable::sptr getDummy() {

}

}  // namespace savable
}  // namespace model