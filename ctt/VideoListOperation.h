


#if !defined(_VIDEOLISTOPERATION_H)
#define _VIDEOLISTOPERATION_H

#include "Operation.h"
#include "Video.h"

class VideoListOperation : public Operation {
public:
	void do();
	void undo();
private:
	Video video;
	int index;
	SavableList<Video> videoList;
};

#endif  //_VIDEOLISTOPERATION_H
