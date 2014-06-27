


#if !defined(_VIDEOWIDGET_H)
#define _VIDEOWIDGET_H

#include "QWidget.h"
#include "Observer.h"
#include "VideoScrubber.h"

class VideoWidget : public QWidget, public Observer {
public:
	void VideoWidget(VideoScrubber scrubber);
	VideoScrubber getScrubber();
};

#endif  //_VIDEOWIDGET_H
