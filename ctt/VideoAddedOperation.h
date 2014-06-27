


#if !defined(_VIDEOADDEDOPERATION_H)
#define _VIDEOADDEDOPERATION_H

#include "VideoListOperation.h"
#include "Video.h"

class VideoAddedOperation : public VideoListOperation {
public:
	void VideoAddedOperation(Video video, SavableList<Video> videoList);
	void do();
	void undo();
};

#endif  //_VIDEOADDEDOPERATION_H
