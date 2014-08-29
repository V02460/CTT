#include "AnalysingWidget.h"

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::difference::FrameDiff;
using ::controller::VideoListController;
using ::controller::DifferenceController;

namespace view {
	AnalysingWidget::AnalysingWidget(SaveableList<FilteredVideo>::sptr filteredVideos, Player::sptr player,
		VideoListController::sptr videoListController, SaveableList<FrameDiff>::sptr differences, QWidget *parent)
		: QWidget(parent), filteredVideos(filteredVideos), player(player) {
		thumbnailWidget = new ThumbnailListWidget(filteredVideos, 9, true, this);
		thumbnailWidget->subscribe(videoListController);
		QObject::connect(thumbnailWidget, SIGNAL(buttonActivated(int)), this, SLOT(videoActivated(int)));
		QObject::connect(thumbnailWidget, SIGNAL(buttonDeactivated(int)), this, SLOT(videoDeactivated(int)));
		QObject::connect(thumbnailWidget, SIGNAL(buttonReplaced(int, int)), this, SLOT(videoReplaced(int, int)));

		mainControlWidget = new MainControlWidget(differences, this);
		mainControlWidget->setPlayer(player);


		setupUi();
	}
}  // namespace view