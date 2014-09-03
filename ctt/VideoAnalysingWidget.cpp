#include "VideoAnalysingWidget.h"

#include <QCoreApplication>
#include <QBoxLayout>

#include "NotImplementedException.h"
#include "FilterFactory.h"
#include "HeatmapOverlay.h"
#include "MacroblockOverlay.h"

//#include "AnalysingOrderingWidget.h"
namespace view {
//	class AnalysingOrderingWidget;
}  // namespace view

namespace view {

using ::exception::NotImplementedException;
using ::controller::OverlayController;
using ::model::player::VideoScrubber;
using ::model::filter::FilterFactory;
using ::model::video::Video;
using ::model::filter::overlay::HeatmapOverlay;
using ::model::filter::FilteredVideo;
using ::model::filter::overlay::MacroblockOverlay;

VideoAnalysingWidget::VideoAnalysingWidget(OverlayController::sptr overlayController,
	                                       VideoScrubber::sptr scrubber,
										   VideoScrubber::sptr histogramScrubber,
										   AnalysingOrderingWidget* orderingWidget) : QWidget(), orderingWidget(orderingWidget), overlayController(overlayController), histogramScrubber(histogramScrubber) {
	histWidget = new HistogramWidget(histogramScrubber, this);
	videoWidget = new VideoWidget(scrubber);
	metadataWidget = new FrameMetadataWidget(scrubber, this);

	QObject::connect(this, SIGNAL(overlayAdded(QString)), overlayController.data(), SLOT(insertOverlay(QString)));
	QObject::connect(this, SIGNAL(overlayAdded(QString, ::model::filter::FilteredVideo::sptr, ::model::filter::FilteredVideo::sptr)),
		overlayController.data(), SLOT(insertOverlayWithPixelDiff(QString, ::model::filter::FilteredVideo::sptr, ::model::filter::FilteredVideo::sptr)));
	QObject::connect(this, SIGNAL(overlayRemoved(int)), overlayController.data(), SLOT(removeOverlay(int)));

	setupUi();
}

void VideoAnalysingWidget::setupUi() {
	QVBoxLayout *mainLayout = new QVBoxLayout();

	QWidget *videoWidgetWrapper = QWidget::createWindowContainer(videoWidget, this, Qt::Widget);
	mainLayout->addWidget(videoWidgetWrapper);

	QHBoxLayout *informationLayout = new QHBoxLayout();
	comboboxOverlay = new QComboBox(this);
	comboboxOverlay->addItem(tr("NO_OVERLAY"));
	QList<QByteArray> overlayIds = FilterFactory::getAllOverlayIDs();
	for (int i = 0; i < overlayIds.size(); i++) {
		if (overlayIds.at(i) == MacroblockOverlay::kFilterID) {
			if (histogramScrubber->getVideo()->getFrame(0)->getMetadata().hasMbType()) {
				comboboxOverlay->addItem(QCoreApplication::translate("Filter", overlayIds.at(i)));
			}
		} else {
			comboboxOverlay->addItem(QCoreApplication::translate("Filter", overlayIds.at(i)));
		}
	}
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

		if (overlayId == HeatmapOverlay::kFilterID) {
			QList<FilteredVideo::sptr> video = orderingWidget->getVideos(1);
			if (video.size() == 1) {
				emit overlayAdded(overlayId, videoWidget->getScrubber()->getVideo().dynamicCast<FilteredVideo>(), video.value(0));
			}
		} else {
			emit overlayAdded(overlayId);
		}
	}
}

VideoScrubber::sptr VideoAnalysingWidget::getVideoScrubber() {
	return videoWidget->getScrubber();
}

VideoScrubber::sptr VideoAnalysingWidget::getHistogramScrubber() {
	return histWidget->getScrubber();
}
}  // namespace view