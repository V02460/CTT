#if !defined(_YUVVIDEOSAVER_H)
#define _YUVVIDEOSAVER_H

namespace model {
namespace video {

#include "VideoSaver.h"
#include "Video.h"

class YUVVideoSaver : public VideoSaver {
public:
	void writeToFile(Video video, QDir path);
};

}  // namespace video
}  // namespace model

#endif  //_YUVVIDEOSAVER_H
