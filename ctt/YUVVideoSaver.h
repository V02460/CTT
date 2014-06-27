


#if !defined(_YUVVIDEOSAVER_H)
#define _YUVVIDEOSAVER_H

#include "VideoSaver.h"
#include "Video.h"

class YUVVideoSaver : public VideoSaver {
public:
	void writeToFile(Video video, QDir path);
};

#endif  //_YUVVIDEOSAVER_H
