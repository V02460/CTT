#include "ProcessingWidget.h"

#include <QSplitter>
#include "FilterController.h"
#include "ExtendedVideoListController.h"
#include "ViewState.h"

using ::model::saveable::SaveableList;
using ::model::player::Player;
using ::model::video::FileVideo;
using ::model::filter::FilteredVideo;
using ::controller::VideoListController;
using ::controller::FilterController;
using ::controller::ExtendedVideoListController;

namespace view {

ProcessingWidget::ProcessingWidget(SaveableList<Player>::sptr players,
	                               SaveableList<FilteredVideo>::sptr filteredVideos,
								   SaveableList<FilteredVideo>::sptr baseVideos,
								   SaveableList<FilteredVideo>::sptr analysingFilteredVideos,
								   VideoListController::sptr analysingVideosController,
								   QWidget *parent)
		: QWidget(parent),
		  players(players),
		  filteredVideos(filteredVideos),
		  analysingFilteredVideos(analysingFilteredVideos),
		  analysingVideosController(analysingVideosController) {

	players->subscribe(this);

	playerWidgetsLayout = new QStackedLayout();

	thumbnailWidget = new ThumbnailListWidget(filteredVideos, 1, false, true);
	ExtendedVideoListController::sptr evlc(new ExtendedVideoListController(baseVideos, filteredVideos, players));
	thumbnailWidget->subscribe(evlc);
	QObject::connect(thumbnailWidget, SIGNAL(buttonActivated(int)), this, SLOT(videoActivated(int)));
	QObject::connect(thumbnailWidget, SIGNAL(buttonDeactivated(int)), this, SLOT(videoDeactivated(int)));
	QObject::connect(thumbnailWidget, SIGNAL(buttonReplaced(int, int)), this, SLOT(videoReplaced(int, int)));

	filterController = FilterController::sptr(new FilterController(FilteredVideo::sptr()));
	mainControlWidget = new MainControlWidget(filterController);

	QWidget *emptyWidget = new QWidget();
	emptyWidget->setMinimumSize(QSize(640, 180));
	emptyWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	playerWidgetsLayout->addWidget(emptyWidget);

	update();

	setupUi();
}

ProcessingWidget::~ProcessingWidget() {
	players->unsubscribe(this);
}

void ProcessingWidget::setupUi() {
	setAccessibleName("ProcessingWidget");
	QSplitter *verticalSplitter = new QSplitter(Qt::Vertical, this);
	verticalSplitter->setAccessibleName("ProcessingWidget->verticalSplitter");

	QWidget *upperWidget = new QWidget(verticalSplitter);
	upperWidget->setAccessibleName("ProcessingWidget->upperWidget");


	QWidget *upperRightWidget = new QWidget(upperWidget);
	upperRightWidget->setAccessibleName("ProcessingWidget->upperRightWidget");
	upperRightWidget->setLayout(playerWidgetsLayout);

	QWidget *upperLeftWidget = new QWidget(upperWidget);
	upperLeftWidget->setAccessibleName("ProcessingWidget->upperLeftWidget");
	QVBoxLayout *upperLeftLayout = new QVBoxLayout();

	btnReady = new QPushButton(upperLeftWidget);
	btnReady->setText(tr("READY"));
	QObject::connect(btnReady, SIGNAL(clicked(bool)), this, SLOT(btnChangeViewClicked(bool)));

	upperLeftLayout->addWidget(thumbnailWidget);
	upperLeftLayout->addWidget(btnReady);

	upperLeftWidget->setLayout(upperLeftLayout);

	QHBoxLayout *upperLayout = new QHBoxLayout();
	upperLayout->setContentsMargins(0, 0, 0, 0);
	upperLayout->addWidget(upperLeftWidget);
	upperLayout->addWidget(upperRightWidget);
	upperWidget->setLayout(upperLayout);

	verticalSplitter->addWidget(upperWidget);
	verticalSplitter->addWidget(mainControlWidget);
	verticalSplitter->setStretchFactor(0, 3);
	verticalSplitter->setStretchFactor(1, 1);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(verticalSplitter);
	setLayout(layout);
	setContentsMargins(0, 0, 0, 0);
}

void ProcessingWidget::videoActivated(int id) {
	//id + 1, da an Stelle 0 ein leeres Widget sitzt
	playerWidgetsLayout->setCurrentIndex(id + 1);
	mainControlWidget->setPlayer(players->get(id));
	mainControlWidget->setVideo(filteredVideos->get(id));
}

void ProcessingWidget::videoReplaced(int oldId, int newId) {
	videoActivated(newId);
}

void ProcessingWidget::videoDeactivated(int id) {
	playerWidgetsLayout->setCurrentIndex(0);
}

void ProcessingWidget::btnChangeViewClicked(bool active) {
	ViewState::getInstance()->changeView(ViewType::ANALYSING_VIEW);
}

void ProcessingWidget::update() {
	for each (PlayerWidget *playerWidget in playerWidgets) {
		playerWidgetsLayout->removeWidget(playerWidget);
		playerWidgets.removeOne(playerWidget);
	}

	for (int i = 0; i < players->getSize(); i++) {
		PlayerWidget *playerWidget = new PlayerWidget(players->get(i), analysingFilteredVideos, analysingVideosController, this);

		playerWidgetsLayout->addWidget(playerWidget);
		playerWidgets.append(playerWidget);
	}

	playerWidgetsLayout->setCurrentIndex(0);
	mainControlWidget->removePlayer();
	mainControlWidget->removeVideo();
}

}// namespace view
