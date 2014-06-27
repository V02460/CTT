


#if !defined(_VIDEOREMOVEDOPERATION_H)
#define _VIDEOREMOVEDOPERATION_H

#include "VideoListOperation.h"

class VideoRemovedOperation : public VideoListOperation {
public:
	void VideoRemovedOperation(int index, int SavableList<Video>);
	void do();
	void undo();
};

#endif  //_VIDEOREMOVEDOPERATION_H
