#include "ViewState.h"

namespace view {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;

ViewState::sptr ViewState::instance = *new QSharedPointer<ViewState>();

ViewState::ViewState() {
	*currentView = ViewType::PROCESSING_VIEW;
	currentMainWindowSize = new QSize(800, 600);
	*lastSelectedFolder = QDir::current();
}

Memento ViewState::getMemento() const {

}

void ViewState::restore(Memento memento) {

}

Saveable::sptr ViewState::getDummy() {

}

void ViewState::changeView(ViewType newView) {

}

ViewState::sptr ViewState::getInstance() {
	if (instance.isNull()) {
		instance = *new QSharedPointer<ViewState>(new ViewState());
	}

	return instance;
}

void ViewState::setMainWindowSize(QSize newSize) {
	*currentMainWindowSize = newSize;
}

void ViewState::setLastSelectedFolder(QDir newDir) {
	*lastSelectedFolder = newDir;
}

const QSize ViewState::getMainWindowSize() {
	return *currentMainWindowSize;
}

const QDir ViewState::getLastSelectedFolder() {
	return *lastSelectedFolder;
}

const ViewType ViewState::getCurrentViewType() {
	return *currentView;
}

}  // namespace view