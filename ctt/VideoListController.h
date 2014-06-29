#if !defined(_VIDEOLISTCONTROLLER_H)
#define _VIDEOLISTCONTROLLER_H

#include "Observer.h"
#include "Video.h"

namespace controller {

/**
*	The VideoListController manages requests to manipulate the VideoList.
**/
class VideoListController : public Observer {
public slots:

	/**
	*	Initiates adding a video to the VideoList.
	*	Is called when a notifaction is received that a video should be added to the VideoList.
	*	@param path The path to the video which is to be added.
	**/
	void addVideo(QString path);

	/**
	*	Initiates adding a video to the VideoList.
	*	Is called when a notifaction is received that a video should be added to the VideoList.
	*	@param video The video which is to be added.
	**/
	void addVideo(Video video);

	/**
	*	Initiates removing a video from the VideoList.
	*	Is called when a notifaction is received that a video should be removed from the VideoList.
	*	@param index The index of the video which is to be removed.
	**/
	void removeVideo(int index);
	
	/**
	*	Initiates removing a video from the VideoList.
	*	Is called when a notifaction is received that a video should be removed from the VideoList.
	*	@param video The video which is to be removed.
	**/
	void removeVideo(Video video);
};

}  // namespace controller

#endif  //_VIDEOLISTCONTROLLER_H
