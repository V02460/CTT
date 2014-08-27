#include "ViewState.h"

#include "NotImplementedException.h"

namespace view {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;

Memento ViewState::getMemento() const {
    throw new NotImplementedException();
}

void ViewState::restore(Memento memento) {
    throw new NotImplementedException();
}

Saveable::sptr ViewState::getDummy() {
    throw new NotImplementedException();
}

void ViewState::changeView(ViewType newView) {
    throw new NotImplementedException();
}

Saveable::SaveableType ViewState::getSaveableType() {
    return SaveableType::viewState;
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

ViewState::ViewState() : currentView(ViewType::PROCESSING_VIEW){}

ViewState::uptr ViewState::instance;
}  // namespace view