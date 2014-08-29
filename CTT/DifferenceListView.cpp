#include "DifferenceListView.h"

using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;
using ::controller::DifferenceController;

namespace view {
	DifferenceListView::DifferenceListView(SaveableList<FrameDiff>::sptr differences,
		DifferenceController::sptr differenceController, QWidget *parent) : AbstractListView(parent) {

	}

	void DifferenceListView::update() {

	}
}  // namespace view