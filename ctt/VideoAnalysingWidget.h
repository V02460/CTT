#ifndef _VIDEOANALYSINGWIDGET_H
#define _VIDEOANALYSINGWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QComboBox>
#include <QString>

#include "OverlayController.h"
#include "VideoWidget.h"
#include "HistogramWidget.h"
#include "FrameMetadataWidget.h"
#include "AnalysingOrderingWidget.h"

namespace view {
/**
 * The VideoAnalysingWidget provides the interactible components for changing the active overlay as well as it holds the
 * means to display a video, its histograms and its frame metadata.
 */
class VideoAnalysingWidget : public QWidget {
    Q_OBJECT
public:
    typedef QScopedPointer<VideoAnalysingWidget> uptr;
    typedef QSharedPointer<VideoAnalysingWidget> sptr;
    typedef QWeakPointer<VideoAnalysingWidget> wptr;

	VideoAnalysingWidget(::controller::OverlayController::sptr overlayController,
		::model::player::VideoScrubber::sptr scrubber, ::model::player::VideoScrubber::sptr historamScrubber, AnalysingOrderingWidget *orderingWidget);

	::model::player::VideoScrubber::sptr getVideoScrubber();
	::model::player::VideoScrubber::sptr getHistogramScrubber();
public slots:
    /**
     * This method is called when the user changes the currently selected overly via the overlay combobox.
     * It emitts the overlayChanged signal
     *
     * @param index The index of the currently chosen overlay in the combobox.
     */
    void comboboxOverlayCurrentIndexChanged(int index);

signals:
    /**
     * This signal is emitted as soon as the currently selected overlay changes.
     */
	void overlayAdded(QString id);

	void overlayAdded(QString id, ::model::filter::FilteredVideo::sptr video1, ::model::filter::FilteredVideo::sptr video2);

	void overlayRemoved(int index);
private:
	void setupUi();

	::controller::OverlayController::sptr overlayController;
	::model::player::VideoScrubber::sptr histogramScrubber;
	AnalysingOrderingWidget *orderingWidget;
    QComboBox *comboboxOverlay; /**< The combobox to choose the active overlay */
    VideoWidget *videoWidget; /**< The VideoWidget where the video actually is displayed */
    HistogramWidget *histWidget; /**< The HistogramWidget which shows the histograms for the current frame */
    FrameMetadataWidget *metadataWidget;/**< The FrameMetadataWidget which displays the metadate for the current frame */
};

}  // namespace view

#endif  //_VIDEOANALYSINGWIDGET_H
