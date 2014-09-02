#include "PlayerWidget.h"

#include <QHBoxLayout>

using ::model::player::Player;
using ::model::player::VideoScrubber;
using ::controller::VideoListController;

namespace view {

PlayerWidget::PlayerWidget(Player::sptr player, VideoListController::sptr controller,
	QWidget *parent) : QWidget(parent) {
	if (player.data() != 0) {
		QList<VideoScrubber::sptr> scrubbers = player->getScrubbers();

		if (scrubbers.size() == 2) {
			inputVideo = new VideoProcessingWidget(scrubbers.at(0), controller, false, this);
			filteredVideo = new VideoProcessingWidget(scrubbers.at(1), controller, true, this);

			setupUi();
		}
	} else {
		qDebug() << "Error in PlayerWidget! Player was empty.";
	}
}

void PlayerWidget::setupUi() {
	setAccessibleName("PlayerWidget");
	QHBoxLayout *layout = new QHBoxLayout();

	layout->addWidget(inputVideo);
	layout->addWidget(filteredVideo);
	inputVideo->setMinimumSize(filteredVideo->minimumSize());

	layout->setStretch(0, 1);
	layout->setStretch(1, 1);

	setLayout(layout);
}

}  // namespace view