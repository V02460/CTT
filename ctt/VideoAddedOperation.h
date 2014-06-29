


#if !defined(_VIDEOADDEDOPERATION_H)
#define _VIDEOADDEDOPERATION_H

#include "VideoListOperation.h"
#include "Video.h"

/**
*	The VideoAddedOperation is providing functionality for doing and undoing adding a Video to a VideoList.
**/
class VideoAddedOperation : public VideoListOperation {
public:

	/**
	*	Constructs an Operation that is responsible for adding a specified Video to a VideoList.
	*	@param video The video which should be added to a list of videos.
	*	@param videoList The list to which a certain video should be added.
	**/
	VideoAddedOperation(Video video, SaveableList<Video> videoList);

	/**
	*	Manages requests to add a Video to a VideoList.
	**/
	void doOperation();

	/**
	*	Manages requests to undo adding a Video to a VideoList.
	**/
	void undo();
};

#endif  //_VIDEOADDEDOPERATION_H
