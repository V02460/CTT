


#if !defined(_HISTOGRAMWIDGET_H)
#define _HISTOGRAMWIDGET_H

#include "Observer.h"
#include "VideoScrubber.h"

/**
 *	The HistogramWidget displays different histograms for a video frame. Therefore it registeres itself at a VideoScrubber to recieve
 *	the histograms
 */
class HistogramWidget : public Observer {
public:
	/**
	 *	Creates a new HistogramWidget with a corresponding VideoScrubber from where it gets the histograms which are displayed
	 *
	 *	@param scrubber The VideoScrubber to register at and which provides the histograms
	 */
	HistogramWidget(VideoScrubber scrubber);
	/**
	 *	Shows the next histogram.
	 *	So for example the widget switches from the histogram for reds to the one for greens
	 */
	void next();
private:
	void paint();
	VideoScrubber scrubber;
};

#endif  //_HISTOGRAMWIDGET_H