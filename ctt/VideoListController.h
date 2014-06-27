


#if !defined(_VIDEOLISTCONTROLLER_H)
#define _VIDEOLISTCONTROLLER_H

#include "Observer.h"
#include "Video.h"

class VideoListController : public Observer {
public:
	slot addVideo(QString path);
	slot addVideo(Video video);
	slot removeVideo(int index);
	slot removeVideo(Video video);
};

#endif  //_VIDEOLISTCONTROLLER_H
