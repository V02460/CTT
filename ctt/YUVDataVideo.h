


#if !defined(_YUVDATAVIDEO_H)
#define _YUVDATAVIDEO_H

#include "Video.h"
#include "Frame.h"
#include "Memento.h"

class YUVDataVideo : public Video {
public:
	VideoMetadata getMetadata();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_YUVDATAVIDEO_H
