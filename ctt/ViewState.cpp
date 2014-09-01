#include "ViewState.h"

#include "NotImplementedException.h"

namespace view {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;

void ViewState::changeView(ViewType newView) {
	currentView = newView;
	changed();
}

ViewState* ViewState::getInstance() {
	if (instance.isNull()) {
		instance.reset(new ViewState());
	}

	return instance.data();
}

const VideoDisplayPolicy* ViewState::getCurrentVideoDisplayPolicy() {
	throw new NotImplementedException();
}

void ViewState::changeVideoDisplayPolicy() {
	throw new NotImplementedException();
}

ViewType ViewState::getCurrentViewType() {
	return currentView;
}

ViewState::ViewState() : Observable(), currentView(ViewType::PROCESSING_VIEW) {}

ViewState::uptr ViewState::instance;

}  // namespace view