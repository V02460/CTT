


#if !defined(_VIDEOSAVERFACTORY_H)
#define _VIDEOSAVERFACTORY_H

#include "Video.h"
#include "VideoFileType.h"

class VideoSaverFactory {
public:
	slot writeVideo(Video video, QDir path, VideoFileType fileType);
};

#endif  //_VIDEOSAVERFACTORY_H
