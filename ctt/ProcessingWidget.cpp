#include "ProcessingWidget.h"
#include "NotImplementedException.h"

#include <QSplitter>
#include "FilterController.h"

using ::model::saveable::SaveableList;
using ::model::player::Player;
using ::model::video::FileVideo;
using ::model::filter::FilteredVideo;
using ::controller::VideoListController;
using ::controller::FilterController;

namespace view {

ProcessingWidget::ProcessingWidget(SaveableList<Player>::sptr players,
	SaveableList<FilteredVideo>::sptr filteredVideos,
	SaveableList<FileVideo>::sptr baseVideos,
	VideoListController::sptr analysingVideosController, QWidget *parent) : QWidget(parent) {
	this->analysingVideosController = analysingVideosController;

	this->players = players;
	players->subscribe(this);

	this->filteredVideos = filteredVideos;

	playerWidgets = new QList<PlayerWidget::sptr>();
	playerWidgetsLayout = new QStackedLayout();

	thumbnailWidget = new ThumbnailListWidget(filteredVideos, 1, false);
	//TODO subscribe ExtendedVideoListController to thumbnailWidget
	QObject::connect(thumbnailWidget, SIGNAL(buttonActivated(int)), this, SLOT(videoActivated(int)));
	QObject::connect(thumbnailWidget, SIGNAL(buttonDeactivated(int)), this, SLOT(videoDeactivated(int)));
	QObject::connect(thumbnailWidget, SIGNAL(buttonReplaced(int, int)), this, SLOT(videoReplaced(int, int)));

	filterController = FilterController::sptr(new FilterController(FilteredVideo::sptr()));
	mainControlWidget = new MainControlWidget(filterController);

	playerWidgetsLayout->addWidget(new QWidget());

	update();

	setupUi();
}

void ProcessingWidget::setupUi() {
	setAccessibleName("ProcessingWidget");
	QSplitter *verticalSplitter = new QSplitter(Qt::Vertical, this);
	verticalSplitter->setAccessibleName("ProcessingWidget->verticalSplitter");

	QWidget *upperWidget = new QWidget(verticalSplitter);
	upperWidget->setAccessibleName("ProcessingWidget->upperWidget");

	QSplitter *horizontalSplitter = new QSplitter(Qt::Horizontal, upperWidget);
	horizontalSplitter->setAccessibleName("ProcessingWidget->horizontalSplitter");

	QWidget *upperRightWidget = new QWidget(horizontalSplitter);
	upperRightWidget->setAccessibleName("ProcessingWidget->upperRightWidget");
	upperRightWidget->setLayout(playerWidgetsLayout);

	QWidget *upperLeftWidget = new QWidget(horizontalSplitter);
	upperLeftWidget->setAccessibleName("ProcessingWidget->upperLeftWidget");
	QVBoxLayout *upperLeftLayout = new QVBoxLayout();

	btnReady = new QPushButton(upperLeftWidget);
	btnReady->setText(tr("READY"));
	QObject::connect(btnReady, SIGNAL(clicked(bool)), this, SLOT(btnChangeViewClicked(bool)));

	upperLeftLayout->addWidget(thumbnailWidget);
	upperLeftLayout->addWidget(btnReady);

	upperLeftWidget->setLayout(upperLeftLayout);

	horizontalSplitter->addWidget(upperLeftWidget);
	horizontalSplitter->addWidget(upperRightWidget);

	QHBoxLayout *upperLayout = new QHBoxLayout();
	upperLayout->addWidget(horizontalSplitter);
	upperWidget->setLayout(upperLayout);

	verticalSplitter->addWidget(upperWidget);
	verticalSplitter->addWidget(mainControlWidget);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(verticalSplitter);
	setLayout(layout);
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

}

void ProcessingWidget::btnChangeViewClicked(bool active) {
	ViewState::getInstance()->changeView(ViewType::ANALYSING_VIEW);
}

void ProcessingWidget::update() {
	for each (PlayerWidget::sptr playerWidget in *playerWidgets) {
		playerWidgetsLayout->removeWidget(playerWidget.data());
		playerWidgets->removeOne(playerWidget);
	}

	for (int i = 0; i < players->getSize(); i++) {
		PlayerWidget::sptr playerWidget = PlayerWidget::sptr(new PlayerWidget(players->get(i), analysingVideosController, this));

		playerWidgetsLayout->addWidget(playerWidget.data());
		playerWidgets->append(playerWidget);
	}

	playerWidgetsLayout->setCurrentIndex(0);
	mainControlWidget->removePlayer();
	mainControlWidget->removeVideo();
}

}// namespace view
