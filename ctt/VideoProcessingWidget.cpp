#include "VideoProcessingWidget.h"

#include "VideoSaver.h"
#include "VideoFileType.h"
#include <QVBoxLayout>
#include <QFileDialog>

namespace view {

VideoProcessingWidget::VideoProcessingWidget(::model::player::VideoScrubber::sptr scrubber,
	::controller::VideoListController::sptr controller, bool showSaveButton, QWidget *parent) : QWidget(parent) {
	if (scrubber.data() != 0) {
		this->videoWidget = new VideoWidget(scrubber);
		this->showSaveButton = showSaveButton;

		setupUi();

		subscribe(controller);
	}
}

void VideoProcessingWidget::checkboxUseForAnalysisValueChanged(int state) {
	if (state = Qt::Checked) {
		emit videoForAnalysingAdded(videoWidget->getScrubber().getVideo());
	} else if (state = Qt::Unchecked) {
		emit videoForAnalysingRemoved(*videoWidget->getScrubber().getVideo().data());
	}
}

void VideoProcessingWidget::btnSaveVideoClicked() {
	QString saveFileName = QFileDialog::getSaveFileName(this, tr("SAVE_VIDEO_DIALOG"));
	model::video::VideoSaver::writeToFile(videoWidget->getScrubber().getVideo(), saveFileName, model::video::VideoFileType::YUV);
}

void VideoProcessingWidget::setupUi() {
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	QHBoxLayout *lowerLayout = new QHBoxLayout(this);

	QWidget *videoWidgetContainer = QWidget::createWindowContainer(videoWidget, this, Qt::Widget);
	mainLayout->addWidget(videoWidgetContainer);

	checkboxUseForAnalysis = new QCheckBox(this);
	checkboxUseForAnalysis->setText(tr("USE_VIDEO_FOR_ANALYSIS"));
	QObject::connect(checkboxUseForAnalysis, SIGNAL(stateChanged(int)), this, SLOT(checkboxUseForAnalysisValueChanged(int)));
	lowerLayout->addWidget(checkboxUseForAnalysis);

	if (showSaveButton) {
		btnSaveVideo = new QPushButton(this);
		btnSaveVideo->setText(tr("SAVE_VIDEO"));
		QObject::connect(btnSaveVideo, SIGNAL(clicked()), this, SLOT(btnSaveVideoClicked()));
		lowerLayout->addWidget(btnSaveVideo);
	}

	mainLayout->addLayout(lowerLayout);

	setLayout(mainLayout);
}

void VideoProcessingWidget::subscribe(::controller::VideoListController::sptr observer) {
	QObject::connect(this, SIGNAL(videoForAnalysingAdded(model::video::Video::sptr)),
		observer.data(), SLOT(addVideo(model::video::Video::sptr)));
	QObject::connect(this, SIGNAL(videoForAnalysingRemoved(const model::video::Video&)),
		observer.data(), SLOT(removeVideo(const model::video::Video&)));
}

void VideoProcessingWidget::unsubscribe(const ::controller::VideoListController &observer) {
	QObject::disconnect(this, SIGNAL(videoForAnalysingAdded(model::video::Video::sptr)),
		&observer, SLOT(addVideo(model::video::Video::sptr)));
	QObject::disconnect(this, SIGNAL(videoForAnalysingRemoved(const model::video::Video&)),
		&observer, SLOT(removeVideo(const model::video::Video&)));
}
}  // namespace view