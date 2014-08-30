#include "ThumbnailListWidget.h"

#include <QFileDialog>
#include <QDialogButtonBox>

#include "YUVType.h"


namespace view {

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::video::YUVType;

ThumbnailListWidget::ThumbnailListWidget(SaveableList<FilteredVideo>::sptr filteredVideos, int selectableCount, bool isHorizontal, QWidget *parent) : QScrollArea(parent), macroblockFilePath("") {
	thumbnailList = QList<ListedPushButton::sptr>();
	activatedButtons = QList<int>();

	this->filteredVideos = filteredVideos;
	if (!filteredVideos.isNull()) {
		filteredVideos->subscribe(this);
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
	setAccessibleName("ThumbnailListWidget");
	if (isHorizontal) {
		thumbnailListLayout = new QHBoxLayout();
		thumbnailListLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	} else {
		thumbnailListLayout = new QVBoxLayout();
		thumbnailListLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	}
	QWidget *scrollWidget = new QWidget(this);
	scrollWidget->setAccessibleName("ThumbnailListWidget->scrollWidget");
	scrollWidget->setLayout(thumbnailListLayout);
	setWidget(scrollWidget);
	setWidgetResizable(true);

	btnAddVideo = new QPushButton(this);
	btnAddVideo->setAccessibleName("ThumbnailListWidget->btnAddVideo");
	btnAddVideo->setMinimumSize(QSize(50, 50));
	btnAddVideo->setText(tr("ADD_VIDEO"));
	thumbnailListLayout->addWidget(btnAddVideo);
	QObject::connect(btnAddVideo, SIGNAL(clicked(bool)), this, SLOT(btnAddVideoClicked(bool)));

	update();

	setupOpenVideoDialog();
}

void ThumbnailListWidget::setupOpenVideoDialog() {
	openVideoDialog = new QDialog(this, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	QGridLayout *dialogMainLayout = new QGridLayout();

	widthSpinBox = new QSpinBox(openVideoDialog);
	widthSpinBox->setMinimum(1);
	QLabel *widthLabel = new QLabel(tr("VIDEO_WIDTH"));
	dialogMainLayout->addWidget(widthLabel, 0, 0);
	dialogMainLayout->addWidget(widthSpinBox, 0, 1);

	heightSpinBox = new QSpinBox(openVideoDialog);
	heightSpinBox->setMinimum(1);
	QLabel *heightLabel = new QLabel(tr("VIDEO_HEIGHT"));
	dialogMainLayout->addWidget(heightLabel, 0, 2);
	dialogMainLayout->addWidget(heightSpinBox, 0, 3);

	yuvType = new QComboBox(openVideoDialog);
	yuvType->addItem(tr("YUV444"));
	yuvType->addItem(tr("YUV422"));
	yuvType->addItem(tr("YUV420"));
	yuvType->setCurrentIndex(0);
	QLabel *yuvTypeLabel = new QLabel(tr("VIDEO_YUV_TYPE"));
	dialogMainLayout->addWidget(yuvTypeLabel, 1, 1);
	dialogMainLayout->addWidget(yuvType, 1, 2);

	fpsSpinBox = new QDoubleSpinBox(openVideoDialog);
	fpsSpinBox->setSuffix(tr(" FPS"));
	fpsSpinBox->setMinimum(1);
	fpsSpinBox->setValue(24);
	QLabel *fpsLabel = new QLabel(tr("VIDEO_FPS"));
	dialogMainLayout->addWidget(fpsLabel, 2, 0);
	dialogMainLayout->addWidget(fpsSpinBox, 2, 1);

	lengthSpinBox = new QSpinBox(openVideoDialog);
	lengthSpinBox->setSuffix(tr(" FRAMES"));
	lengthSpinBox->setMinimum(1);
	lengthSpinBox->setValue(2);
	QLabel *lengthLabel = new QLabel(tr("VIDEO_LENGTH"));
	dialogMainLayout->addWidget(lengthLabel, 2, 2);
	dialogMainLayout->addWidget(lengthSpinBox, 2, 3);

	macroblockFileLabel = new QLabel(tr("NO_MACROOBLOCK_FILE_CHOSEN"));
	QPushButton *macroblockFile = new QPushButton(tr("ADD_MACROBLOCK_FILE"));
	QObject::connect(macroblockFile, SIGNAL(clicked(bool)), this, SLOT(btnAddMacroblockFileClicked(bool)));
	dialogMainLayout->addWidget(macroblockFileLabel, 3, 0, 1, 3);
	dialogMainLayout->addWidget(macroblockFile, 3, 3);

	QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, openVideoDialog);
	dialogMainLayout->addWidget(buttonBox, 4, 0);
	QObject::connect(buttonBox, SIGNAL(accepted()), openVideoDialog, SLOT(accept()));
	QObject::connect(buttonBox, SIGNAL(rejected()), openVideoDialog, SLOT(reject()));

	openVideoDialog->setLayout(dialogMainLayout);
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
	//TODO muss bei der dynamischen neuerstellung ggf. angepasst werden
	thumbnailListLayout->addStretch();

	//TODO activatedButton entweder leeren oder die buttons anpassen
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

void ThumbnailListWidget::listedButtonRemoved(bool checked, int id) {
	if (activatedButtons.contains(id)) {
		thumbnailList.at(id)->setChecked(false);
	}

	emit videoRemoved(id);
}

void ThumbnailListWidget::btnAddVideoClicked(bool checked) {
	QString videoPath = QFileDialog::getOpenFileName(0, tr("OPEN_VIDEO"), "", tr("YUV_FILES (*.yuv)"));
	if (videoPath != "") {
		openVideoDialog->exec();

		if (openVideoDialog->result() == QDialog::Accepted) {
			YUVType videoType;

			switch (yuvType->currentIndex()) {
			case 0: videoType = YUVType::YUV444; break;
			case 1: videoType = YUVType::YUV422; break;
			case 2: videoType = YUVType::YUV420; break;
			default: break;
			}

			if (macroblockFilePath != "") {
				emit videoAdded(videoPath, macroblockFileLabel->text(), widthSpinBox->value(), heightSpinBox->value(),
					fpsSpinBox->value(), videoType, static_cast<unsigned int>(lengthSpinBox->value()));
			} else {
				emit videoAdded(videoPath, widthSpinBox->value(), heightSpinBox->value(), fpsSpinBox->value(),
					videoType, static_cast<unsigned int>(lengthSpinBox->value()));
			}
		}
	}
}

void ThumbnailListWidget::btnAddMacroblockFileClicked(bool checked) {
	macroblockFilePath = QFileDialog::getOpenFileName(0, tr("OPEN_VIDEO"), "", tr("DAT_FILES (*.dat)"));
	if (macroblockFilePath != "") {
		macroblockFileLabel->setText(macroblockFilePath);
	}
}

const QList<int> ThumbnailListWidget::getActiveIndices() {
	return activatedButtons;
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