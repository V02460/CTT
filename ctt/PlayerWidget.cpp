#include "PlayerWidget.h"

#include <QHBoxLayout>

namespace view {

PlayerWidget::PlayerWidget(model::player::Player::sptr player, ::controller::VideoListController::sptr controller,
	QWidget *parent = 0) : QWidget(parent) {
	QList<model::player::VideoScrubber::sptr> scrubbers = player->getScrubbers();

	if (scrubbers.size() == 2) {
		inputVideo = new VideoProcessingWidget(scrubbers.at(0), controller, false, this);
		filteredVideo = new VideoProcessingWidget(scrubbers.at(1), controller, true, this);

		setupUi();
	}
}

void PlayerWidget::setupUi() {
	QHBoxLayout *layout = new QHBoxLayout(this);

	layout->addWidget(inputVideo);
	layout->addWidget(filteredVideo);

	setLayout(layout);
}

}  // namespace view