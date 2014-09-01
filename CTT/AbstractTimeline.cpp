#include "AbstractTimeline.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

void AbstractTimeline::update() {
	throw NotImplementedException();
}

}  // namespace view