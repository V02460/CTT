#include "Saveable.h"

#include "NotImplementedException.h"

namespace model {
namespace saveable {

using ::exception::NotImplementedException;

bool Saveable::isDummy() const {
	return isDummyFlag;
}

Saveable::sptr getDummy() {
    throw new NotImplementedException();
}

}  // namespace savable
}  // namespace model