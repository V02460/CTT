#include "ThumbnailListWidget.h"

#include <QFileDialog>


namespace view {

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;

ThumbnailListWidget::ThumbnailListWidget(SaveableList<FilteredVideo>::sptr filteredVideos, int selectableCount, bool isHorizontal, QWidget *parent) : QScrollArea(parent){
	thumbnailList = QList<ListedPushButton::sptr>();
	activatedButtons = QList<int>();

	this->filteredVideos = filteredVideos;
	if (filteredVideos.data() != 0) {
		filteredVideos->subscribe(ThumbnailListWidget::sptr(this));
	} else {
		qDebug() << "Error in ThumbnailListWidget! The filteredVideo list was null! Using list with 5 empty elements instead";
		this->filteredVideos = SaveableList<FilteredVideo>::sptr(new SaveableList<FilteredVideo>());

		for (int i = 0; i < 5; i++) {
			this->filteredVideos->insert(i, FilteredVideo::sptr());
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
	QWidget *scrollWidget = new QWidget(this);
	scrollWidget->setLayout(thumbnailListLayout);
	setWidget(scrollWidget);
	setWidgetResizable(true);

	btnAddVideo = new QPushButton(this);
	btnAddVideo->setMinimumSize(QSize(50, 50));
	btnAddVideo->setText(tr("ADD_VIDEO"));
	thumbnailListLayout->addWidget(btnAddVideo);
	QObject::connect(btnAddVideo, SIGNAL(clicked(bool)), this, SLOT(btnAddVideoClicked(bool)));

	update();
}

void ThumbnailListWidget::update() {
	//Remove all contents of the ThumbnailListWidget

	//Remove and delete all ListedPushButtons of this widget
	for each (ListedPushButton::sptr btn in thumbnailList) {
		thumbnailListLayout->removeWidget(btn.data());
		thumbnailList.removeOne(btn);
		btn->setChecked(false);
		QObject::disconnect(btn.data(), SIGNAL(toggled(bool, int)), this, SLOT(listedButtonToggled(bool, int)));
	}

	thumbnailListLayout->removeWidget(btnAddVideo);

	//Repopulate the ThumbnailListWidget
	//TODO ggf auf unsigned int umschreiben
	for (int i = 0; i < filteredVideos->getSize(); i++) {
		ListedPushButton::sptr addedButton =
			ListedPushButton::sptr(new ListedPushButton(i, filteredVideos->get(i), this));
		thumbnailList.insert(i, addedButton);
		thumbnailListLayout->addWidget(addedButton.data());
		QObject::connect(addedButton.data(), SIGNAL(toggled(bool, int)), this, SLOT(listedButtonToggled(bool, int)));
	}

	thumbnailListLayout->addWidget(btnAddVideo);

	adjustSize();
}

void ThumbnailListWidget::listedButtonToggled(bool checked, int id) {
	if (checked && !activatedButtons.contains(id)) {
		if (activatedButtons.size() < selectableCount) {
			activatedButtons.append(id);
			emit buttonActivated(id);
		} else {
			int oldActiveId = activatedButtons.at(0);
			activatedButtons.removeFirst();
			activatedButtons.append(id);
			thumbnailList.at(oldActiveId)->setChecked(false);
			emit buttonReplaced(oldActiveId, id);
		}
	} else if (!checked && activatedButtons.contains(id)) {
		if (activatedButtons.size() > 1) {
			activatedButtons.removeOne(id);
			emit buttonDeactivated(id);
		}
		else {
			thumbnailList.at(id)->setChecked(true);
		}
	}
}

void ThumbnailListWidget::btnAddVideoClicked(bool checked) {
	QString videoPath = QFileDialog::getOpenFileName(0, tr("OPEN_VIDEO"), "", tr("ALL_FILES (*.*)"));
	emit videoAdded(videoPath);
}

void ThumbnailListWidget::subscribe(::controller::VideoListController::sptr observer) {
	QObject::connect(this, SIGNAL(videoAdded(QString)), observer.data(), SLOT(addVideo(QString)));
	QObject::connect(this, SIGNAL(videoRemoved(int)), observer.data(), SLOT(removeVideo(int)));
}

void ThumbnailListWidget::unsubscribe(const ::controller::VideoListController &observer) {
	QObject::disconnect(this, SIGNAL(videoAdded(QString)), &observer, SLOT(addVideo(QString)));
	QObject::disconnect(this, SIGNAL(videoRemoved(int)), &observer, SLOT(removeVideo(int)));
}

}  // namespace view