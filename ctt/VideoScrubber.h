


#if !defined(_VIDEOSCRUBBER_H)
#define _VIDEOSCRUBBER_H

#include "Savable.h"
#include "Observable.h"
#include "Frame.h"
#include "Video.h"
#include "VideoMetadata.h"
#include "Memento.h"

class VideoScrubber : public Savable, public Observable {
public:
	virtual slot jumpToFrameNr(int frameNumber) = 0;
	Frame getCurrentFrame();
	void VideoScrubber(Video video);
	void VideoScrubber(Video video, int frameNumber);
	VideoMetadata getVideoMetadata();
	Video getVideo();
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
private:
	Video *video;
	Frame *currentFrame;
};

#endif  //_VIDEOSCRUBBER_H
