#include "ViewState.h"

#include "NotImplementedException.h"

namespace view {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;

Memento ViewState::getMemento() const {
    throw NotImplementedException();
}

void ViewState::restore(Memento memento) {
    throw NotImplementedException();
}

Saveable::sptr ViewState::getDummy() {
	// TODO absprachebedarf!
    throw NotImplementedException();
}

void ViewState::changeView(ViewType newView) {
	currentView = newView;
	changed();
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
	throw NotImplementedException();
}

void ViewState::changeVideoDisplayPolicy() {
	throw NotImplementedException();
}

ViewType ViewState::getCurrentViewType() {
	return currentView;
}

ViewState::ViewState() : currentView(ViewType::PROCESSING_VIEW){}

ViewState::uptr ViewState::instance;
}  // namespace view