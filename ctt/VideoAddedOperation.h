#if !defined(_VIDEOADDEDOPERATION_H)
#define _VIDEOADDEDOPERATION_H

#include "VideoListOperation.h"
#include "Video.h"

namespace controller {
namespace operation {

class VideoAddedOperation : public VideoListOperation {
public:
	void VideoAddedOperation(Video video, SaveableList<Video> videoList);
	void do();
	void undo();
};

}  // namespace operation
}  // namespace controller

#endif  //_VIDEOADDEDOPERATION_H
