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

Saveable::SaveableType ViewState::getType() const {
	return Saveable::SaveableType::viewState;
}

QSharedPointer<ViewState> ViewState::getInstance() {
	throw new NotImplementedException();
}

QSharedPointer<VideoDisplayPolicy> ViewState::getCurrentVideoDisplayPolicy() {
	throw new NotImplementedException();
}

void ViewState::changeVideoDisplayPolicy() {
	throw new NotImplementedException();
}

}  // namespace view