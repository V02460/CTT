#include "VideoProcessingWidget.h"
#include "ViewState.h"
#include "VideoSaver.h"
#include "IllegalArgumentException.h"
#include <QFileDialog>

namespace view {

	VideoProcessingWidget::VideoProcessingWidget(model::player::VideoScrubber::sptr scrubber, bool showSaveButton, QWidget *parent) {
	this->setParent(parent);
	videoWidget = new VideoWidget(scrubber);
	this->showSaveButton = showSaveButton;
	this->scrubber = scrubber;
	setupUi();
}

void VideoProcessingWidget::checkboxUseForAnalysisStateChanged(int state) {
	if (state == Qt::CheckState::Checked) {
		emit videoForAnalysingAdded(scrubber->getVideo);
	} else if (state == Qt::CheckState::Unchecked) {
		emit videoForAnalysingRemoved(scrubber->getVideo);
	}
}

void VideoProcessingWidget::btnSaveVideoClicked() {
	//TODO ggf. filter einfuegen
	QString fileName = QFileDialog::getSaveFileName(this,
		QApplication::translate("videoProcessingWidget", "SAVE_VIDEO_DIALOG"),
		ViewState::getInstance()->getLastSelectedFolder().absolutePath());
	QFileInfo *file = new QFileInfo(fileName);
	
	if (file) {
		ViewState::getInstance()->setLastSelectedFolder(file->dir());
		try {
			model::video::VideoFileType requestedFileType = model::video::VideoSaver::convertStringToVideoFileType(
				file->completeSuffix());
			emit saveVideo(scrubber->getVideo(), file, requestedFileType);
		} catch (exception::IllegalArgumentException e) {
			//TODO Reaktion auf falschen Dateityp
		}
	}
}

void VideoProcessingWidget::setupUi() {
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("videoProcessingWidget"));
	//this->resize(600, 400);
	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(2);
	verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	verticalLayout->setContentsMargins(0, 0, 0, 0);
	videoWidget->setObjectName(QStringLiteral("videoWidget"));
	videoWidget->setMaximumSize(QSize(16777215, 16777215));

	verticalLayout->addWidget(videoWidget);

	controlsWidget = new QWidget(this);
	controlsWidget->setObjectName(QStringLiteral("controlsWidget"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(controlsWidget->sizePolicy().hasHeightForWidth());
	controlsWidget->setSizePolicy(sizePolicy);
	controlsWidget->setMaximumSize(QSize(16777215, 30));
	horizontalLayout = new QHBoxLayout(controlsWidget);
	horizontalLayout->setSpacing(6);
	horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
	horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
	horizontalLayout->setContentsMargins(0, 0, 0, 0);
	checkboxUseForAnalysis = new QCheckBox(controlsWidget);
	checkboxUseForAnalysis->setObjectName(QStringLiteral("checkBoxUseForAnalysis"));

	horizontalLayout->addWidget(checkboxUseForAnalysis);

	if (showSaveButton) {
		btnSaveVideo = new QPushButton(controlsWidget);
		btnSaveVideo->setObjectName(QStringLiteral("btnSaveVideo"));

		horizontalLayout->addWidget(btnSaveVideo);
	}


	verticalLayout->addWidget(controlsWidget);


	retranslateUi();

	connect(checkboxUseForAnalysis, SIGNAL(stateChanged(int)), this, SLOT(checkboxUseForAnalysisStateChanged(int)));
	connect(btnSaveVideo, SIGNAL(clicked(bool)), this, SLOT(btnSaveVideoClicked()));
}

void VideoProcessingWidget::retranslateUi() {
	//videoProcessingWidget->setWindowTitle(QApplication::translate("videoProcessingWidget", "Form", 0));
	checkboxUseForAnalysis->setText(QApplication::translate("videoProcessingWidget", "USE_FOR_ANALYSIS", 0));
	if (showSaveButton) {
		btnSaveVideo->setText(QApplication::translate("videoProcessingWidget", "SAVE_VIDEO", 0));
	}
}

}  // namespace view