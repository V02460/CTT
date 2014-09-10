#include "DifferenceListView.h"

#include "DifferenceListViewItem.h"
#include "ViewState.h"

using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;
using ::controller::DifferenceController;
using ::model::player::Player;

namespace view {
	DifferenceListView::DifferenceListView(SaveableList<FrameDiff>::sptr differences,
		DifferenceController::sptr differenceController, Player::sptr player, QWidget *parent) : AbstractListView(parent), 
		differences(differences), differenceController(differenceController), player(player) {
		differences->subscribe(this);

		QObject::connect(this, SIGNAL(elementRemoved(int)), differenceController.data(), SLOT(diffRemoved(int)));
		update();
	}

	DifferenceListView::~DifferenceListView() {
		differences->unsubscribe(this);
	}

	void DifferenceListView::update() {
		removeAllItems();
		for (int i = 0; i < differences->getSize(); i++) {
			items.append(new DifferenceListViewItem(differences->get(i), player, ViewState::getColorFromIndex(i), this));
		}
		setupUi();
	}
}  // namespace view