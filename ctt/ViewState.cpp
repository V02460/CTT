#include "ViewState.h"

namespace view {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;

Memento ViewState::getMemento() const {

}

void ViewState::restore(Memento memento) {

}

Saveable::sptr ViewState::getDummy() {

}

void ViewState::changeView(ViewType newView) {

}

}  // namespace view