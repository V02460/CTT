#include "PlayerWidget.h"

#include <QHBoxLayout>

namespace view {

using ::model::player::Player;
using ::model::player::VideoScrubber;
using ::controller::VideoListController;

PlayerWidget::PlayerWidget(Player::sptr player, VideoListController::sptr controller, QWidget *parent)
        : QWidget(parent) {
	if (player.isNull()) {
        throw IllegalArgumentException("Player must not be empty.");
    }
	
    QList<VideoScrubber::sptr> scrubbers = player->getScrubbers();
    if (scrubbers.size() != 2) {
        throw IllegalArgumentException("Player must contain exactly two scrubbers.");
    }

	inputVideo = new VideoProcessingWidget(scrubbers[0], controller, false, this);
	filteredVideo = new VideoProcessingWidget(scrubbers[1], controller, true, this);

	setupUi();
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