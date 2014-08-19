#include "ProcessingWidget.h"

#include <QSplitter>
#include "FilterController.h"

namespace view {

ProcessingWidget::ProcessingWidget(::model::saveable::SaveableList<::model::player::Player>::sptr players,
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos,
	::model::saveable::SaveableList<::model::video::FileVideo>::sptr baseVideos, 
	::controller::VideoListController::sptr analysingVideosController, QWidget *parent = 0) : QWidget(parent) {
	this->analysingVideosController = analysingVideosController;
	playerWidgets = new QList<PlayerWidget::sptr>();
	playerWidgetsLayout = new QStackedLayout(this);

	thumbnailWidget = new ThumbnailListWidget(filteredVideos, 1, false, this);
	//TODO subscribe ExtendedVideoListController to thumbnailWidget
	QObject::connect(thumbnailWidget, SIGNAL(buttonActivated(int)), this, SLOT(videoActivated(int)));
	QObject::connect(thumbnailWidget, SIGNAL(buttonDeactivated(int)), this, SLOT(videoDeactivated(int)));
	QObject::connect(thumbnailWidget, SIGNAL(buttonReplaced(int, int)), this, SLOT(videoReplaced(int, int)));

	controller::FilterController::sptr filterController = controller::FilterController::sptr(new controller::FilterController());
	mainControlWidget = new MainControlWidget(filterController, this);
	QObject::connect(this, SIGNAL(videoChanged(model::filter::FilteredVideo::sptr)),
		filterController.data(), SLOT(setVideo(model::filter::FilteredVideo::sptr)));

	update();

	setupUi();
}

void ProcessingWidget::setupUi() {
	QSplitter *horizontalSplitter = new QSplitter(Qt::Horizontal, this);

	QWidget *upperWidget = new QWidget(horizontalSplitter);

	QSplitter *verticalSplitter = new QSplitter(Qt::Vertical, upperWidget);

	QWidget *upperRightWidget = new QWidget(verticalSplitter);
	setLayout(playerWidgetsLayout);

	QWidget *upperLeftWidget = new QWidget(verticalSplitter);
	QVBoxLayout *upperLeftLayout = new QVBoxLayout(upperLeftWidget);

	btnReady = new QPushButton(upperLeftWidget);
	btnReady->setText(tr("READY"));
	QObject::connect(btnReady, SIGNAL(clicked(bool)), this, SLOT(btnChangeViewClicked(bool)));

	upperLeftLayout->addWidget(thumbnailWidget);
	upperLeftLayout->addWidget(btnReady);

	upperLeftWidget->setLayout(upperLeftLayout);

	verticalSplitter->addWidget(upperLeftWidget);
	verticalSplitter->addWidget(upperRightWidget);

	QHBoxLayout *upperLayout = new QHBoxLayout(upperWidget);
	upperLayout->addWidget(verticalSplitter);
	upperWidget->setLayout(upperLayout);

	horizontalSplitter->addWidget(upperWidget);
	horizontalSplitter->addWidget(mainControlWidget);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(horizontalSplitter);
	setLayout(layout);
}

void ProcessingWidget::videoActivated(int id) {
	playerWidgetsLayout->setCurrentIndex(id);
	mainControlWidget->setPlayer(players->get(id));
	emit videoChanged(players->get(id)->getScrubbers().at(1)->getVideo());
}

void ProcessingWidget::videoReplaced(int oldId, int newId) {
	videoActivated(newId);
}

void ProcessingWidget::videoDeactivated(int id) {

}

void ProcessingWidget::btnChangeViewClicked(bool active) {

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
}

}  // namespace view