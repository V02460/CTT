#if !defined(_VIDEOLISTCONTROLLER_H)
#define _VIDEOLISTCONTROLLER_H

#include "Observer.h"
#include "Video.h"

namespace controller {

class VideoListController : public Observer {
public:
	slot addVideo(QString path);
	slot addVideo(Video video);
	slot removeVideo(int index);
	slot removeVideo(Video video);
};

}  // namespace controller

#endif  //_VIDEOLISTCONTROLLER_H
