#include "VideoProcessingWidget.h"

#include "VideoSaver.h"
#include "VideoFileType.h"
#include "IOException.h"
#include "AccessToDummyException.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

using ::exception::IOException;
using ::exception::AccessToDummyException;
using ::model::player::VideoScrubber;
using ::controller::VideoListController;
using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::video::Video;

namespace view {

VideoProcessingWidget::VideoProcessingWidget(VideoScrubber::sptr scrubber,
	                                         SaveableList<FilteredVideo>::sptr filteredVideos,
	                                         VideoListController::sptr controller,
											 bool showSaveButton, QWidget *parent) : QWidget(parent),
											                                         filteredVideos(filteredVideos) {
	if (!scrubber.isNull()) {
		this->videoWidget = new VideoWidget(scrubber);
		this->showSaveButton = showSaveButton;

		setupUi();

		subscribe(controller);
		filteredVideos->subscribe(this);
	}
}

VideoProcessingWidget::~VideoProcessingWidget() {
	filteredVideos->unsubscribe(this);
}

void VideoProcessingWidget::checkboxUseForAnalysisValueChanged(int state) {
	if (state == Qt::Checked) {
		emit videoForAnalysingAdded(videoWidget->getScrubber()->getVideo());
	} else if (state == Qt::Unchecked) {
		emit videoForAnalysingRemoved(*videoWidget->getScrubber()->getVideo().data());
	}
}

void VideoProcessingWidget::btnSaveVideoClicked() {
	QString saveFileName = QFileDialog::getSaveFileName(this, tr("SAVE_VIDEO_DIALOG"), "", tr("YUV_FILES *.yuv"));
	if (saveFileName.endsWith(".yuv")) {
		saveFileName = saveFileName.mid(0, saveFileName.length() - 4);
	}

	try {
		Video::sptr video = videoWidget->getScrubber()->getVideo();
		saveFileName.append("_" + QString::number(video->getResolution().width()) + "x" + QString::number(video->getResolution().height()) + "_YUV444_" + QString::number(video->getMetadata().getFPS(), 'g', 2).replace('.', ',') + "FPS.yuv");
		video->save(saveFileName, model::video::VideoFileType::YUV);
	}
	catch (IOException e) {
		QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_SAVING_FAILED_IO_TITLE"), tr("VIDEO_SAVING_FAILED_IO_DETAILS"), QMessageBox::Ok, this);
		errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

		errorBox.exec();
	}
	catch (AccessToDummyException e) {
		QMessageBox errorBox(QMessageBox::Critical, tr("VIDEO_SAVING_FAILED_DUMMY_TITLE"), tr("VIDEO_SAVING_FAILED_DUMMY_DETAILS"), QMessageBox::Ok, this);
		errorBox.setDetailedText(e.getName() + "\n" + e.getMsg());

		errorBox.exec();
	}
}

void VideoProcessingWidget::setupUi() {
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *lowerLayout = new QHBoxLayout();

	QWidget *videoWidgetContainer = QWidget::createWindowContainer(videoWidget, this, Qt::Widget);
	mainLayout->addWidget(videoWidgetContainer);

	checkboxUseForAnalysis = new QCheckBox(this);
	checkboxUseForAnalysis->setText(tr("USE_VIDEO_FOR_ANALYSIS"));
	QObject::connect(checkboxUseForAnalysis, SIGNAL(stateChanged(int)), this, SLOT(checkboxUseForAnalysisValueChanged(int)));
	lowerLayout->addWidget(checkboxUseForAnalysis);

	btnSaveVideo = new QPushButton(this);
	btnSaveVideo->setText(tr("SAVE_VIDEO"));
	QObject::connect(btnSaveVideo, SIGNAL(clicked()), this, SLOT(btnSaveVideoClicked()));
	lowerLayout->addWidget(btnSaveVideo);

	checkboxUseForAnalysis->setFixedHeight(btnSaveVideo->height());

	if (!showSaveButton) {
		btnSaveVideo->hide();
	}
	//checkboxUseForAnalysis->setMinimumHeight(btnSaveVideo->minimumHeight());

	mainLayout->addLayout(lowerLayout);

	setLayout(mainLayout);

	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void VideoProcessingWidget::subscribe(::controller::VideoListController::sptr observer) {
	QObject::connect(this, SIGNAL(videoForAnalysingAdded(::model::video::Video::sptr)),
		observer.data(), SLOT(addVideo(::model::video::Video::sptr)));
	QObject::connect(this, SIGNAL(videoForAnalysingRemoved(const ::model::video::Video&)),
		observer.data(), SLOT(removeVideo(const ::model::video::Video&)));

	this->videoListController = observer;
}

void VideoProcessingWidget::unsubscribe(const ::controller::VideoListController &observer) {
	QObject::disconnect(this, SIGNAL(videoForAnalysingAdded(::model::video::Video::sptr)),
		&observer, SLOT(addVideo(::model::video::Video::sptr)));
	QObject::disconnect(this, SIGNAL(videoForAnalysingRemoved(const ::model::video::Video&)),
		&observer, SLOT(removeVideo(const ::model::video::Video&)));
}

void VideoProcessingWidget::update() {
	bool isUsedForAnalysis = false;
	for (int i = 0; i < filteredVideos->getSize(); i++) {
		if (filteredVideos->get(i)->getBaseVideo() == videoWidget->getScrubber()->getVideo()) {
			isUsedForAnalysis = true;
			break;
		}
	}

	bool oldState = checkboxUseForAnalysis->blockSignals(true);
	checkboxUseForAnalysis->setChecked(isUsedForAnalysis);
	checkboxUseForAnalysis->blockSignals(oldState);
}

}  // namespace view