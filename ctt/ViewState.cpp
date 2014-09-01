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

QColor ViewState::getColorFromIndex(int index) {
	int hueStep = (index * 10);
	int hue = hueStep % 360;
	int saturationStep = ((hueStep / 360) * 16);
	int saturation = 255 - (saturationStep % 256);
	int valueStep = (saturationStep / 256) * 16;
	int value = 255 - ((valueStep % 256));

	return QColor::fromHsv(hue , saturation, value);
}

ViewState::ViewState() : currentView(ViewType::PROCESSING_VIEW){}

ViewState::uptr ViewState::instance;
}  // namespace view