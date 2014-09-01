#include "DifferenceListView.h"

#include "DifferenceListViewItem.h"

using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;
using ::controller::DifferenceController;
using ::model::player::Player;

namespace view {
	DifferenceListView::DifferenceListView(SaveableList<FrameDiff>::sptr differences, Player::sptr player,
		QWidget *parent) : AbstractListView(parent) , differences(differences), player(player) {
		differences->subscribe(this);
		update();
	}

	void DifferenceListView::update() {
		removeAllItems();
		for (int i = 0; i < differences->getSize(); i++) {
			items.append(new DifferenceListViewItem(differences->get(i), player, this));
		}
		setupUi();
	}
}  // namespace view