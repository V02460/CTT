


#if !defined(_VIDEOSAVER_H)
#define _VIDEOSAVER_H

#include "Video.h"

class VideoSaver {
public:
	virtual void writeToFile(Video video, QDir path) = 0;
};

#endif  //_VIDEOSAVER_H
