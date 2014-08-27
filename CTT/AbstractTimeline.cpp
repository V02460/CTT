#include "AbstractTimeline.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

void AbstractTimeline::update() {
	throw new NotImplementedException();
}

}  // namespace view