


#if !defined(_DATAVIDEO_H)
#define _DATAVIDEO_H

#include "Video.h"
#include "Frame.h"
#include "Memento.h"
#include "VideoReader.h"

class DataVideo : public Video {
public:
	void DataVideo(Path path);
	VideoMetadata getMetadata();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
private:
	VideoReader *reader;
};

#endif  //_DATAVIDEO_H
