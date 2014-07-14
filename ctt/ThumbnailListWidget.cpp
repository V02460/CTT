#include "ThumbnailListWidget.h"
#include <QFileDialog>
#include "ViewState.h"

namespace view {

ThumbnailListWidget::ThumbnailListWidget(::model::saveable::SaveableList<::model::player::Player>::sptr players,
	QWidget *parent) {
	this->setParent(parent);
	this->players = players;
	thumbnailList = new QList<QPushButton>();

	setupUi();
}

void ThumbnailListWidget::setupUi() {
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("thumbnailListWidget"));
	//this->resize(150, 300);
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	verticalLayout->setContentsMargins(2, 2, 2, 2);
	verticalLayout->setSpacing(5);
	for (int i = 0; i < players->getSize(); i++) {
		QPushButton *thumbnailButton = new QPushButton(this);
		//thumbnailList->append(*thumbnailButton);
		verticalLayout->addWidget(thumbnailButton);
	}
	btnAddVideo = new QPushButton(this);
	btnAddVideo->setObjectName(QStringLiteral("btnAddVideo"));
	btnAddVideo->setText("ADD_VIDEO");

	verticalLayout->addWidget(btnAddVideo);

	connect(btnAddVideo, SIGNAL(clicked(bool)), this, SLOT(btnAddVideoClicked()));

	resizeButtons();
	retranslateUi();

}

void ThumbnailListWidget::update() {
	setupUi();
}

void ThumbnailListWidget::btnAddVideoClicked() {
	QString fileName = QFileDialog::getOpenFileName(this, QApplication::translate("thumbnailListWidget", "OPEN_VIDEO_DIALOG", 0),
		ViewState::getInstance()->getLastSelectedFolder().absolutePath());
	QFileInfo *file = new QFileInfo(fileName);
	if (file) {
		ViewState::getInstance()->setLastSelectedFolder(file->dir());
		emit videoAdded(*file);
	}
}

void ThumbnailListWidget::resizeButtons() {
	QSize *buttonSize = new QSize(this->width(), (9 * this->width()) / 16);
	/*for (int i = 0; i < thumbnailList->size(); i++) {
		QPushButton *tmp = &thumbnailList->value(i);
		tmp->setFixedSize(*buttonSize);
		tmp->setIconSize(*buttonSize);

		if (players->getSize() >= 2) {
			QImage scaledImage = players->get(i).getScrubbers().value(1)->getVideo()
				->getScaledFrame(17, *buttonSize)->getFramebufferObject()->toImage();
			QIcon *icon = new QIcon(QPixmap::fromImage(scaledImage));
			tmp->setIcon(*icon);
		}
	}*/
	//btnAddVideo->setFixedSize(*buttonSize);
	//btnAddVideo->setIconSize(*buttonSize);

	//TODO btnAddvideo set icon !!!
}

void ThumbnailListWidget::resizeEvent(QResizeEvent *ev) {
	resizeButtons();
}

void ThumbnailListWidget::retranslateUi() {
	//TODO bei fehlendem Bild eine Fehlermeldung auf den Button schreiben
}
}  // namespace view