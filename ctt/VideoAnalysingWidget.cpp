#include "VideoAnalysingWidget.h"

#include <QCoreApplication>
#include <QBoxLayout>

#include "FilterFactory.h"
#include "HeatmapOverlay.h"
#include "MacroblockOverlay.h"

//#include "AnalysingOrderingWidget.h"
namespace view {
//	class AnalysingOrderingWidget;
}  // namespace view

namespace view {

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
	videoWidgetWrapper->setMinimumSize(QSize(320, 180));
	mainLayout->addWidget(videoWidgetWrapper);

	QWidget *informationWidget = new QWidget(this);
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
	informationWidget->setLayout(informationLayout);

	QPushButton *btnToggleInformation = new QPushButton(tr("SHOW_INFORMATION"), this);
	btnToggleInformation->setCheckable(true);
	btnToggleInformation->setChecked(true);
	QObject::connect(btnToggleInformation, SIGNAL(toggled(bool)), informationWidget, SLOT(setVisible(bool)));

	mainLayout->addWidget(btnToggleInformation);

	mainLayout->addWidget(informationWidget);
	mainLayout->setStretch(0, 5);
	mainLayout->setStretch(2, 1);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(mainLayout);

	setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
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