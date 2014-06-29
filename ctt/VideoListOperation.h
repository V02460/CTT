


#if !defined(_VIDEOLISTOPERATION_H)
#define _VIDEOLISTOPERATION_H

#include "Operation.h"
#include "Video.h"

/**
*	The VideoListOperation is providing functionality for doing and undoing manipulations of the VideoList which is used for generating test videos or analysing.
**/
class VideoListOperation : public Operation {
public:

	/**
	*	Manages requests to manipulate the VideoList which is used for generating test videos or analysing.
	**/
	void doOperation();

	/**
	*	Manages requests to undo manipulations of the VideoList which is used for generating test videos or analysing.
	**/
	void undoOperation();
private:
	Video video;
	int index;
	SavableList<Video> videoList;
};

#endif  //_VIDEOLISTOPERATION_H
