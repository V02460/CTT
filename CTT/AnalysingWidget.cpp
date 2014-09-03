#include "AnalysingWidget.h"

#include <QSplitter>

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::difference::FrameDiff;
using ::controller::VideoListController;
using ::controller::DifferenceController;

namespace view {
	AnalysingWidget::AnalysingWidget(SaveableList<FilteredVideo>::sptr filteredVideos, Player::sptr player,
		VideoListController::sptr videoListController, SaveableList<FrameDiff>::sptr differences, QWidget *parent)
		: QWidget(parent) {
		thumbnailWidget = ThumbnailListWidget::sptr(new ThumbnailListWidget(filteredVideos, 9, true, this));
		thumbnailWidget->subscribe(videoListController);

		videoDisplay = AnalysingOrderingWidget::sptr(new AnalysingOrderingWidget(filteredVideos, player, thumbnailWidget, this));
		QObject::connect(thumbnailWidget.data(), SIGNAL(buttonActivated(int)), videoDisplay.data(), SLOT(videoActivated(int)));
		QObject::connect(thumbnailWidget.data(), SIGNAL(buttonDeactivated(int)), videoDisplay.data(), SLOT(videoDeactivated(int)));
		QObject::connect(thumbnailWidget.data(), SIGNAL(buttonReplaced(int, int)), videoDisplay.data(), SLOT(videoReplaced(int, int)));

		mainControlWidget = new MainControlWidget(differences, player, videoDisplay, this);
		mainControlWidget->setPlayer(player);

		setupUi();
	}

	void AnalysingWidget::setupUi() {
		QSplitter *verticalSplitter = new QSplitter(Qt::Vertical, this);

		verticalSplitter->addWidget(thumbnailWidget.data());
		verticalSplitter->addWidget(videoDisplay.data());
		verticalSplitter->addWidget(mainControlWidget);
		verticalSplitter->setStretchFactor(0, 1);
		verticalSplitter->setStretchFactor(1, 5);
		verticalSplitter->setStretchFactor(2, 2);

		QVBoxLayout *layout = new QVBoxLayout();
		layout->addWidget(verticalSplitter);
		setLayout(layout);
	}
}  // namespace view