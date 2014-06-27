


#if !defined(_EXTENDEDTIMELINE_H)
#define _EXTENDEDTIMELINE_H

#include "Observer.h"
#include "Observable.h"
#include "ViewState.h"
#include "FilteredVideo.h"

class ExtendedTimeline : public Observer, public Observable {
public:
	ViewState viewState;
	slot sldStateChanged();
	slot timelineStateChanged();
	slot changeActiveVideo(FilteredVideo video);
	slot changeSize(double zoomFactor);
	slot changeViewState();
private:
	QSlider sliderProgress;
};

#endif  //_EXTENDEDTIMELINE_H
