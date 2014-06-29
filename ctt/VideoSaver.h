#if !defined(_VIDEOSAVER_H)
#define _VIDEOSAVER_H

#include "Video.h"

namespace model {
namespace video {

class VideoSaver {
public:
	virtual void writeToFile(Video video, QDir path) = 0;
};

}  // namespace video
}  // namespace model

#endif  //_VIDEOSAVER_H
