#if !defined(_VIDEOREMOVEDOPERATION_H)
#define _VIDEOREMOVEDOPERATION_H

#include "VideoListOperation.h"

namespace controller {
namespace operation {

class VideoRemovedOperation : public VideoListOperation {
public:
	void VideoRemovedOperation(int index, int SaveableList<Video>);
	void do();
	void undo();
};

}  // namespace operation
}  // namespace controller

#endif  //_VIDEOREMOVEDOPERATION_H
