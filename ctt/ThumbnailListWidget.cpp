#include "ThumbnailListWidget.h"

#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QRegExp>
#include <QImageReader>
#include "YUVType.h"
#include "FileNotFoundException.h"
#include "IOException.h"
#include "FFmpegException.h"


namespace view {

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::video::YUVType;
using ::controller::VideoListController;
using ::exception::FileNotFoundException;
using ::exception::IOException;
using ::exception::FFmpegException;

ThumbnailListWidget::ThumbnailListWidget(SaveableList<FilteredVideo>::sptr filteredVideos,
	                                     int selectableCount,
										 bool isHorizontal,
										 bool autoActivate,
										 QWidget *parent) : QScrollArea(parent),
										                    macroblockFilePath(""),
															activatedButtons(),
															thumbnailList(),
															backupThumbnailList(),
															ffmpegWorks(true),
															filteredVideos(filteredVideos),
															selectableCount(selectableCount),
															isHorizontal(isHorizontal),
															autoActivate(autoActivate) {

	if (!filteredVideos.isNull()) {
		filteredVideos->subscribe(this);
	} else {
		qDebug() << "Error in ThumbnailListWidget! The filteredVideo list was null! Using list with 5 empty elements instead";
		this->filteredVideos = SaveableList<FilteredVideo>::sptr(new SaveableList<FilteredVideo>());

		for (int i = 0; i < 5; i++) {
			this->filteredVideos->insert(i, FilteredVideo::sptr());
		}
	}

	setupUi();
}

ThumbnailListWidget::~ThumbnailListWidget() {
	filteredVideos->unsubscribe(this);
}

void ThumbnailListWidget::setupUi() {
	setAccessibleName("ThumbnailListWidget");
	if (isHorizontal) {
		thumbnailListLayout = new QHBoxLayout();
		thumbnailListLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		setMinimumHeight(ListedPushButton::MINIMUM_SIZE.height() + 30);
		setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	} else {
		thumbnailListLayout = new QVBoxLayout();
		thumbnailListLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
		setMinimumWidth(ListedPushButton::MINIMUM_SIZE.width() + 30);
		setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
	}
	thumbnailListLayout->setContentsMargins(5, 5, 5, 5);

	QWidget *scrollWidget = new QWidget(this);
	scrollWidget->setAccessibleName("ThumbnailListWidget->scrollWidget");
	scrollWidget->setLayout(thumbnailListLayout);
	setWidget(scrollWidget);
	setWidgetResizable(true);

	btnAddVideo = new QPushButton(this);
	btnAddVideo->setAccessibleName("ThumbnailListWidget->btnAddVideo");
	btnAddVideo->setMinimumSize(ListedPushButton::MINIMUM_SIZE);
	
	QString addVideoIconPath = "Resources/Icons/video.png";
	if (!QImageReader::imageFormat(addVideoIconPath).isEmpty()) {
		btnAddVideo->setIcon(QIcon(addVideoIconPath));
		btnAddVideo->setIconSize(btnAddVideo->size()*0.80);
		btnAddVideo->setToolTip(tr("ADD_VIDEO"));
	} else {
		btnAddVideo->setText(tr("ADD_VIDEO"));
	}

	thumbnailListLayout->addWidget(btnAddVideo);
	QObject::connect(btnAddVideo, SIGNAL(clicked(bool)), this, SLOT(btnAddVideoClicked(bool)));

	thumbnailListLayout->addStretch(5);

	update();

	setupOpenVideoDialog();
}

void ThumbnailListWidget::setupOpenVideoDialog() {
	openVideoDialog = new QDialog(this, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	QGridLayout *dialogMainLayout = new QGridLayout();

	widthSpinBox = new QSpinBox(openVideoDialog);
	widthSpinBox->setMinimum(1);
	widthSpinBox->setMaximum(5000);
	QLabel *widthLabel = new QLabel(tr("VIDEO_WIDTH"));
	dialogMainLayout->addWidget(widthLabel, 0, 0);
	dialogMainLayout->addWidget(widthSpinBox, 0, 1);

	heightSpinBox = new QSpinBox(openVideoDialog);
	heightSpinBox->setMinimum(1);
	heightSpinBox->setMaximum(5000);
	QLabel *heightLabel = new QLabel(tr("VIDEO_HEIGHT"));
	dialogMainLayout->addWidget(heightLabel, 0, 2);
	dialogMainLayout->addWidget(heightSpinBox, 0, 3);

	yuvType = new QComboBox(openVideoDialog);
	yuvType->addItem(tr("YUV444"));
	yuvType->addItem(tr("YUV422"));
	yuvType->addItem(tr("YUV420"));
	yuvType->setCurrentIndex(0);
	QLabel *yuvTypeLabel = new QLabel(tr("VIDEO_YUV_TYPE"));
	dialogMainLayout->addWidget(yuvTypeLabel, 1, 0);
	dialogMainLayout->addWidget(yuvType, 1, 1);

	fpsSpinBox = new QDoubleSpinBox(openVideoDialog);
	fpsSpinBox->setSuffix(tr(" FPS"));
	fpsSpinBox->setMinimum(1);
	fpsSpinBox->setMaximum(1000);
	fpsSpinBox->setValue(24);
	QLabel *fpsLabel = new QLabel(tr("VIDEO_FPS"));
	dialogMainLayout->addWidget(fpsLabel, 1, 2);
	dialogMainLayout->addWidget(fpsSpinBox, 1, 3);

	hdtv = new QCheckBox(openVideoDialog);
	hdtv->setText(tr("USE_HDTV_YUV_TO_RGB_CONVERSION"));
	dialogMainLayout->addWidget(hdtv, 2, 0, 1, 4);

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
	openVideoDialog->layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void ThumbnailListWidget::update() {
	backupThumbnailList.clear();
	for (int i = 0; i < std::min(thumbnailList.length(), filteredVideos->getSize());) {
		ListedPushButton::sptr button = thumbnailList[i];
		if (button->getVideo() != filteredVideos->get(i)) {
			thumbnailListLayout->removeWidget(button.data());
			button->hide();
			button->setChecked(false);
			QObject::disconnect(button.data(), SIGNAL(toggled(bool, int)),
				                this, SLOT(listedButtonToggled(bool, int)));
			QObject::disconnect(button.data(), SIGNAL(removed(bool, int)),
				                this, SLOT(listedButtonRemoved(bool, int)));
			thumbnailList.removeOne(button);
			backupThumbnailList.append(button);
		} else {
			button->setChecked(false);
			button->setIndex(i++);
		}
	}
	while (thumbnailList.length() > filteredVideos->getSize()) {
		ListedPushButton::sptr button = thumbnailList.takeAt(filteredVideos->getSize());
		thumbnailListLayout->removeWidget(button.data());
		button->hide();
		button->setChecked(false);
		QObject::disconnect(button.data(), SIGNAL(toggled(bool, int)),
			this, SLOT(listedButtonToggled(bool, int)));
		QObject::disconnect(button.data(), SIGNAL(removed(bool, int)),
			this, SLOT(listedButtonRemoved(bool, int)));
		backupThumbnailList.append(button);
	}
	while (thumbnailList.length() < filteredVideos->getSize()) {
		int index = thumbnailList.length();
		ListedPushButton::sptr button(new ListedPushButton(index, filteredVideos->get(index)));
		thumbnailList.insert(index, button);
		thumbnailListLayout->insertWidget(index, button.data());
		QObject::connect(button.data(), SIGNAL(toggled(bool, int)), this, SLOT(listedButtonToggled(bool, int)));
		QObject::connect(button.data(), SIGNAL(removed(bool, int)), this, SLOT(listedButtonRemoved(bool, int)));
		if (autoActivate) { button->setChecked(true); }
	}

	delete thumbnailListLayout->takeAt(thumbnailList.length() + 1);
	thumbnailListLayout->addStretch(5);
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
			ListedPushButton::sptr deactivatedButton = thumbnailList.at(oldActiveId);
			bool oldState = deactivatedButton->blockSignals(true);
			deactivatedButton->setChecked(false);
			deactivatedButton->blockSignals(oldState);
			emit buttonReplaced(oldActiveId, id);
		}
	} else if (!checked && activatedButtons.contains(id)) {
		activatedButtons.removeOne(id);
		emit buttonDeactivated(id);
	}
}

void ThumbnailListWidget::listedButtonRemoved(bool checked, int id) {
	if (activatedButtons.contains(id)) {
		//thumbnailList.value(id)->setChecked(false);
		activatedButtons.removeOne(id);
		emit buttonDeactivated(id);
	}

	emit videoRemoved(id);
}

void ThumbnailListWidget::btnAddVideoClicked(bool checked) {
	QString supportedFileTypes = tr("YUV_FILES (*.yuv)");

	if (ffmpegWorks) {
		supportedFileTypes += ";;" + tr("OTHER_VIDEO_FILES (*.avi *.flv *.mpg *.mpeg *.mpeg1 *.mpeg2 *.mpeg4 *.ogg *.ts *.wmv)");
		supportedFileTypes += ";;" + tr("ALL_FILES (*.*)");
	}

	QString videoPath = QFileDialog::getOpenFileName(0, tr("OPEN_VIDEO"), "", supportedFileTypes);
	if (videoPath != "") {
		if (!videoPath.endsWith(".yuv") && ffmpegWorks) {
			openFFMPEGVideo(videoPath);
		} else {
			openYUVVideo(videoPath);
		}
	}
}

void ThumbnailListWidget::openYUVVideo(QString videoPath) {
	QFileInfo fileInfo = QFileInfo(videoPath);
	openVideoDialog->setWindowTitle(tr("MORE_VIDEO_INFORMATION") + ": " + fileInfo.baseName());

	if (fileInfo.baseName().contains("444"))
	{
		yuvType->setCurrentIndex(0);
	}
	if (fileInfo.baseName().contains("422"))
	{
		yuvType->setCurrentIndex(1);
	}
	if (fileInfo.baseName().contains("420"))
	{
		yuvType->setCurrentIndex(2);
	}

	QRegExp resolutionStringRegEx("((\\d+)x(\\d+))");

	if (fileInfo.baseName().contains(resolutionStringRegEx))
	{

		resolutionStringRegEx.indexIn(fileInfo.baseName());
		QStringList widthAndHeight = resolutionStringRegEx.capturedTexts()[0].split("x");

		widthSpinBox->setValue(widthAndHeight[0].toInt());
		heightSpinBox->setValue(widthAndHeight[1].toInt());
	}

	QRegExp fpsStringRegEx("(\\d+,)?\\d+((fps|framespersecond)|FPS)");

	if (fileInfo.baseName().contains(fpsStringRegEx))
	{

		fpsStringRegEx.indexIn(fileInfo.baseName());
		QString fps = fpsStringRegEx.capturedTexts()[0];
		fps.remove(QRegExp("((fps|framespersecond)|FPS)"));
		fps.replace(",", ".");
		fpsSpinBox->setValue(fps.toDouble());
	}

	if (fileInfo.baseName().contains(QRegExp("(hdtv|HDTV)"))) {
		hdtv->setChecked(true);
	}
	else {
		hdtv->setChecked(false);
	}

	macroblockFileLabel->setText(tr("NO_MACROOBLOCK_FILE_CHOSEN"));
	macroblockFilePath = "";

	if (openVideoDialog->exec() == QDialog::Accepted) {
		YUVType videoType;

		switch (yuvType->currentIndex()) {
		case 0: videoType = YUVType::YUV444; break;
		case 1: videoType = YUVType::YUV422; break;
		case 2: videoType = YUVType::YUV420; break;
		default: break;
		}

		try {
			if (macroblockFilePath != "") {
				emit videoAdded(videoPath, macroblockFileLabel->text(), widthSpinBox->value(), heightSpinBox->value(),
					fpsSpinBox->value(), videoType, hdtv->isChecked());
			}
			else {
				emit videoAdded(videoPath, widthSpinBox->value(), heightSpinBox->value(), fpsSpinBox->value(),
					videoType, hdtv->isChecked());
			}
		}
		catch (IllegalArgumentException e) {
			QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_ADDING_FAILED_ILLEGEAL_ARGUMENT_TITLE"), tr("VIDEO_ADDING_FAILED_ILLEGAL_ARGUMENT_DETAILS"), QMessageBox::Ok, this);
			errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

			errorBox.exec();
		}
		catch (FileNotFoundException e) {
			QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_ADDING_FAILED_FILE_NOT_FOUND_TITLE"), tr("VIDEO_ADDING_FAILED_FILE_NOT_FOUND_DETAILS"), QMessageBox::Ok, this);
			errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

			errorBox.exec();
		}
		catch (IOException e) {
			QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_ADDING_FAILED_IO_TITLE"), tr("VIDEO_ADDING_FAILED_IO_DETAILS"), QMessageBox::Ok, this);
			errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

			errorBox.exec();
		}
	}
}


void ThumbnailListWidget::openFFMPEGVideo(QString videoPath) {
	try {
		emit videoAdded(videoPath);
	}
	catch (IllegalArgumentException e) {
		QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_ADDING_FAILED_ILLEGEAL_ARGUMENT_TITLE"), tr("VIDEO_ADDING_FAILED_ILLEGAL_ARGUMENT_DETAILS"), QMessageBox::Ok, this);
		errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

		errorBox.exec();
	}
	catch (FileNotFoundException e) {
		QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_ADDING_FAILED_FILE_NOT_FOUND_TITLE"), tr("VIDEO_ADDING_FAILED_FILE_NOT_FOUND_DETAILS"), QMessageBox::Ok, this);
		errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

		errorBox.exec();
	}
	catch (IOException e) {
		QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_ADDING_FAILED_IO_TITLE"), tr("VIDEO_ADDING_FAILED_IO_DETAILS"), QMessageBox::Ok, this);
		errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

		errorBox.exec();
	}
	catch (FFmpegException e) {
		QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_ADDING_FAILED_FFMEPG_TITLE"), tr("VIDEO_ADDING_FAILED_FFMEPG_DETAILS"), QMessageBox::Ok, this);
		errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

		errorBox.exec();
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

const int ThumbnailListWidget::getSelectableCount() {
	return selectableCount;
}

void ThumbnailListWidget::subscribe(::controller::VideoListController::sptr observer) {
	QObject::connect(this, SIGNAL(videoAdded(QString, QString, int, int, double, model::video::YUVType, bool)),
		observer.data(), SLOT(addVideo(QString, QString, int, int, double, model::video::YUVType, bool)));
	QObject::connect(this, SIGNAL(videoAdded(QString, int, int, double, model::video::YUVType, bool)),
		observer.data(), SLOT(addVideo(QString, int, int, double, model::video::YUVType, bool)));
	QObject::connect(this, SIGNAL(videoAdded(QString)), observer.data(), SLOT(addVideo(QString)));
	QObject::connect(this, SIGNAL(videoRemoved(int)), observer.data(), SLOT(removeVideo(int)));
	videoListController = observer;
}

void ThumbnailListWidget::unsubscribe(const ::controller::VideoListController &observer) {
	QObject::disconnect(this, SIGNAL(videoAdded(QString, QString, int, int, double, model::video::YUVType, bool)),
		&observer, SLOT(addVideo(QString, QString, int, int, double, model::video::YUVType, bool)));
	QObject::disconnect(this, SIGNAL(videoAdded(QString, int, int, double, model::video::YUVType, bool)),
		&observer, SLOT(addVideo(QString, int, int, double, model::video::YUVType, bool)));
	QObject::disconnect(this, SIGNAL(videoRemoved(int)), &observer, SLOT(removeVideo(int)));
	QObject::disconnect(this, SIGNAL(videoAdded(QString)), &observer, SLOT(addVideo(QString)));
}

}  // namespace view