#include "ThumbnailListWidget.h"

namespace view {

using ::model::saveable::SaveableList;
using ::model::video::Video;

ThumbnailListWidget::ThumbnailListWidget(SaveableList<Video>::sptr filteredVideos, int selectableCount, bool isHorizontal, QWidget *parent) : QScrollArea(parent){
	thumbnailList = QList<ListedPushButton::sptr>();
	this->filteredVideos = filteredVideos;
	if (filteredVideos.data() != 0) {
		filteredVideos->subscribe(ThumbnailListWidget::sptr(this));
	} else {
		qDebug() << "Error in ThumbnailListWidget! The filteredVideo list was null! Using list with 5 empty elements instead";
		filteredVideos = SaveableList<Video>::sptr(new SaveableList<Video>());

		for (int i = 0; i < 5; i++) {
			filteredVideos->insert(i, Video::sptr());
		}
	}

	this->selectableCount = selectableCount;
	this->isHorizontal = isHorizontal;

	setupUi();
}

void ThumbnailListWidget::setupUi() {
	if (isHorizontal) {
		thumbnailListLayout = new QHBoxLayout(this);
	} else {
		thumbnailListLayout = new QVBoxLayout(this);
	}
	thumbnailListLayout->setAlignment(Qt::AlignCenter);
	setLayout(thumbnailListLayout);

	setWidgetResizable(true);

	btnAddVideo = new QPushButton(this);
	btnAddVideo->setMinimumSize(QSize(70, 70));
	btnAddVideo->setText(tr("ADD_VIDEO"));
	thumbnailListLayout->addWidget(btnAddVideo);

	update();
}

void ThumbnailListWidget::update() {
	//Remove all contents of the ThumbnailListWidget
	for each (ListedPushButton::sptr btn in thumbnailList) {
		thumbnailListLayout->removeWidget(btn.data());
		thumbnailList.removeOne(btn);
	}

	thumbnailListLayout->removeWidget(btnAddVideo);

	//Repopulate the ThumbnailListWidget
	//TODO ggf auf unsigned int umschreiben
	for (int i = 0; i < filteredVideos->getSize(); i++) {
		ListedPushButton::sptr addedButton = 
			ListedPushButton::sptr(new ListedPushButton(i, filteredVideos->get(i), this));
		thumbnailList.insert(i, addedButton);
		thumbnailListLayout->addWidget(addedButton.data());
	}

	thumbnailListLayout->addWidget(btnAddVideo);
}

}  // namespace view