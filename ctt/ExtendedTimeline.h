#if !defined(_EXTENDEDTIMELINE_H)
#define _EXTENDEDTIMELINE_H

#include "Observer.h"
#include "Observable.h"
#include "ViewState.h"
#include "FilteredVideo.h"
#include "AbstractTimeline.h"
#include <QWidget>
#include <QSlider>

namespace view {

/**
 *	The ExtendedTimeline manages the shown timeline and the navigation of the videos in a given player.
 */
class ExtendedTimeline : public Observer, public Observable, public QWidget {
public slots:
	/**
	 *	Adjusts the timeline to the frame the progress silder is pointing at and signals the change of the current frame to connected slots
	 */
	void sldStateChanged();

	/**
	 *	Adjusts the progress slider to the frame the user has chosen and signals the change of the current frame to connected slots
	 */
	void timelineStateChanged();

	/**
	 *	Adjusts the size of the whole ExtendedTimeline to zoom in to or out of the timeline of a video
	 *
	 *	@param zoomFactor The factor by which the timeline is to be reduced or enlarged
	 */
	void changeSize(double zoomFactor);

	/**
	 *	Adjusts the ExtendedTimeline to the current state of the whole GUI.
	 *	That means that the internal timeline is changed to a timeline of another type (Filter to Difference or vice versa) and the slider is set to the current frame
	 */
	void changeViewState();

private:
	QSlider sliderProgress; /**< This is the slider to naviagte the video */
	ViewState viewState; /**< This is the current state of the whole GUI */
	AbstractTimeline currentTimeline; /**< This is the currently shown timeline. It's either a FilterTimeline or a DifferenceTimeline */
};

}  // namespace view

#endif  //_EXTENDEDTIMELINE_H
