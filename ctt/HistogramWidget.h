#ifndef _HISTOGRAMWIDGET_H
#define _HISTOGRAMWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>

#include "qcustomplot.h"

#include "Observer.h"
#include "VideoScrubber.h"

namespace view {

/**
 * The HistogramWidget displays different histograms for a video frame.
 * Therefore it registers itself at a VideoScrubber to receive the histograms.
 */
class HistogramWidget : public QWidget, public::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<HistogramWidget> uptr;
    typedef QSharedPointer<HistogramWidget> sptr;
    typedef QWeakPointer<HistogramWidget> wptr;

    /**
     * Creates a new HistogramWidget with a corresponding VideoScrubber from where it gets the histograms which are
     * displayed.
     *
     * @param scrubber The VideoScrubber to register at and which provides the histograms.
     */
    HistogramWidget(::model::player::VideoScrubber::sptr scrubber, QWidget *parent = 0);

	~HistogramWidget();

	virtual void update() Q_DECL_OVERRIDE;

	::model::player::VideoScrubber::sptr getScrubber();

public slots:
    /**
     * Shows the next histogram.
     * So for example the widget switches from the histogram for reds to the one for greens.
     */
    void next();

	void toggleAutoRecalculation();

private slots:
	void recalculateHistogram();
private:
	void setupUi();

	QString currentHistogramType;
	QCustomPlot *histogramPlot;
	QCPBars *histogramBars;
	double histogramMaxY;
	QPushButton *btnAutoRecalculation;
	bool autoRecalculation;
    ::model::player::VideoScrubber::sptr scrubber /**< The scrubber at which the HistogramWidget is registered */;
};

}  // namespace view

#endif  //_HISTOGRAMWIDGET_H