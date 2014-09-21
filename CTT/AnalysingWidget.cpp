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
		thumbnailWidget = ThumbnailListWidget::sptr(new ThumbnailListWidget(filteredVideos, 4, false, false));
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

		QHBoxLayout *upperLayout = new QHBoxLayout();
		upperLayout->addWidget(thumbnailWidget.data());
		upperLayout->addWidget(videoDisplay.data());

		QWidget *upperWidget = new QWidget(verticalSplitter);
		upperWidget->setLayout(upperLayout);

		verticalSplitter->addWidget(upperWidget); 
		verticalSplitter->addWidget(mainControlWidget);

		verticalSplitter->setStretchFactor(0, 4);
		verticalSplitter->setStretchFactor(1, 1);

		QVBoxLayout *layout = new QVBoxLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		layout->addWidget(verticalSplitter);
		setLayout(layout);
		setContentsMargins(0, 0, 0, 0);
	}
}  // namespace view