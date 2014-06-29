


#if !defined(_VIDEOANALYSINGWIDGET_H)
#define _VIDEOANALYSINGWIDGET_H

#include "VideoWidget.h"
#include "HistogramWidget.h"
#include "FrameMetadataWidget.h"
#include <QWidget>
#include <QComboBox>
#include <QString>
/**
 *	The VideoAnalysingWidget provides the interactible components for changing the active overlay as well as it holds the means to
 *	display a video´, its histograms and its frame metadata
 */
class VideoAnalysingWidget : public QWidget {
public:
	/**
	 *	Returns the identifier string of the currently chosen overlay.
	 *
	 *	@return The identifier string of the currentyl chosen overlay as defined in the OverlayFactory
	 */
	QString getOverlay();
public slots:
	/**
	 * This method is called when the user changes the currently selected overly via the overlay combobox.
	 * It emitts the overlayChanged signal
	 *
	 *	@param index The index of the currently chosen overlay in the combobox
	 */
	void comboboxOverlayCurrentIndexChanged(int index);
signals:
	/**
	 *	This signal is emitted as soon as the currently selected overlay changes.
	 */
	void overlayChanged();
private:
	QComboBox comboboxOverlay; /**< The combobox to choose the active overlay */
	VideoWidget videoWidget; /**< The VideoWidget where the video actually is displayed */
	HistogramWidget histWidget; /**< The HistogramWidget which shows the histograms for the current frame */
	FrameMetadataWidget metadataWidget;/**< The FrameMetadataWidget which displays the metadate for the current frame */
};

#endif  //_VIDEOANALYSINGWIDGET_H
