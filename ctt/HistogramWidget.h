#ifndef _HISTOGRAMWIDGET_H
#define _HISTOGRAMWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>

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
    HistogramWidget(::model::player::VideoScrubber::sptr scrubber);

    /**
     * Shows the next histogram.
     * So for example the widget switches from the histogram for reds to the one for greens.
     */
    void next();
private:
    void paint();
    ::model::player::VideoScrubber::sptr scrubber /**< The scrubber at which the HistogramWidget is registered */;
};

}  // namespace view

#endif  //_HISTOGRAMWIDGET_H