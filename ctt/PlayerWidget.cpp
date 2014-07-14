#include "PlayerWidget.h"
#include "VideoScrubber.h"

namespace view {

PlayerWidget::PlayerWidget(model::player::Player player) {
	QList<model::player::VideoScrubber::sptr> scrubbers = player.getScrubbers();

	if (scrubbers.size() == 2) {
		inputVideoProcessingWidget = new VideoProcessingWidget(scrubbers.value(0), false);
		outputVideoProcessingWidget = new VideoProcessingWidget(scrubbers.value(1), true);
	} else {
		//TODO Fehlerbehandlung
	}

	setupUi();
}

void PlayerWidget::getActivationSignal() {
	emit playerActivated(*this);
}

void PlayerWidget::setupUi() {
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("playerWidget"));
	//this->resize(600, 400);
	horizontalLayout = new QHBoxLayout(this);
	horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
	horizontalLayout->setContentsMargins(0, 0, 0, 0);
	inputVideoProcessingWidget->setObjectName(QStringLiteral("inputVideoProcessingWidget"));

	horizontalLayout->addWidget(inputVideoProcessingWidget);

	outputVideoProcessingWidget->setObjectName(QStringLiteral("outputVideoProcessingWidget"));

	horizontalLayout->addWidget(outputVideoProcessingWidget);


}

}  // namespace view