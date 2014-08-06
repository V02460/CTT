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

}  // namespace view