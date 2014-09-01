#include "DifferenceTimeline.h"

#include <QHBoxLayout>

using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;
using ::model::player::Player;

namespace view {
	DifferenceTimeline::DifferenceTimeline(SaveableList<FrameDiff>::sptr differences, Player::sptr player, QWidget *parent) : AbstractTimeline(parent), differences(differences), player(player) {
		differences->subscribe(this);
		player->subscribe(this);

		frameCount = player->getVideoLength();
		currentFrameNumber = player->getCurrentFrameNumber();

		setupUi();
		update();
	}

	void DifferenceTimeline::update() {
		if (currentFrameNumber != player->getCurrentFrameNumber()) {
			//TODO range anpassen
		} else if (frameCount != player->getVideoLength()) {
			//TODO range anpassen
		} else {
			updateDifferences();
		}
	}

	void DifferenceTimeline::setupUi() {
		graphPlot = new QCustomPlot(this);

		QHBoxLayout *layout = new QHBoxLayout(this);
		layout->addWidget(graphPlot);

		setLayout(layout);
	}

	void DifferenceTimeline::updateDifferences() {
		for (int i = 0; i < differences->getSize(); i++) {
			for (int j = 0; j < differences->get(i)->getFrameCount(); j++) {

			}
		}
	}
}  // namespace view