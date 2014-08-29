#include "VideoAnalysingWidget.h"

#include <QBoxLayout>

#include "NotImplementedException.h"
#include "FilterFactory.h"

namespace view {

using ::exception::NotImplementedException;
using ::controller::OverlayController;
using ::model::player::VideoScrubber;
using ::model::filter::FilterFactory;
using ::model::video::Video;

VideoAnalysingWidget::VideoAnalysingWidget(OverlayController::sptr overlayController, VideoScrubber::sptr scrubber,
	QWidget *parent) : QWidget(parent) {
	histWidget = new HistogramWidget(scrubber, this);
	videoWidget = new VideoWidget(scrubber);
	metadataWidget = new FrameMetadataWidget(scrubber, this);

	setupUi();
}

void VideoAnalysingWidget::setupUi() {
	QVBoxLayout *mainLayout = new QVBoxLayout();

	QWidget *videoWidgetWrapper = QWidget::createWindowContainer(videoWidget, this, Qt::Widget);
	mainLayout->addWidget(videoWidgetWrapper);

	QHBoxLayout *informationLayout = new QHBoxLayout();
	comboboxOverlay = new QComboBox(this);
	comboboxOverlay->addItem(tr("NO_OVERLAY"));
	comboboxOverlay->addItems(FilterFactory::getAllOverlayIDs());
	comboboxOverlay->setCurrentIndex(0);
	QObject::connect(comboboxOverlay, SIGNAL(currentIndexChanged(int)),
		this, SLOT(comboboxOverlayCurrentIndexChanged(int)));
	informationLayout->addWidget(comboboxOverlay);

	informationLayout->addWidget(histWidget);

	informationLayout->addWidget(metadataWidget);

	mainLayout->addLayout(informationLayout);

	setLayout(mainLayout);
}

void VideoAnalysingWidget::comboboxOverlayCurrentIndexChanged(int index) {
	emit overlayRemoved(0);

	if (index > 0) {
		QString overlayId = FilterFactory::getAllOverlayIDs().at(index - 1);

		if (index == 1) {
			//TODO Request video for difference
			emit overlayAdded(overlayId, Video::sptr());
		} else {
			emit overlayAdded(overlayId);
		}
	}
}

}  // namespace view