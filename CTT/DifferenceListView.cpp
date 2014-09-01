#include "DifferenceListView.h"

using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;
using ::controller::DifferenceController;

namespace view {
	DifferenceListView::DifferenceListView(SaveableList<FrameDiff>::sptr differences
		, QWidget *parent) : AbstractListView(parent) , differences(differences) {
		differences->subscribe(this);
		update();
	}

	void DifferenceListView::update() {
		removeAllItems();
		for (int i = 0; i < differences->getSize(); i++) {
			//TODO DifferenceListViewItem einfügen
		}
		setupUi();
	}
}  // namespace view