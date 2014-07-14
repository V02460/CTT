#include "ViewState.h"

#include "NotImplementedException.h"

namespace view {

using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;

ViewState::sptr ViewState::instance = *new QSharedPointer<ViewState>();

ViewState::ViewState() {
	currentView = ViewType::PROCESSING_VIEW;
	currentMainWindowSize = new QSize(800, 600);
	lastSelectedFolder = new QDir(*new QString("C:\\"));
}

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
	return currentView;
}

}  // namespace view