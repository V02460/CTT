


#if !defined(_FFMPEGDATAVIDEO_H)
#define _FFMPEGDATAVIDEO_H

#include "Video.h"
#include "Frame.h"
#include "Memento.h"

class FFmpegDataVideo : public Video {
public:
	VideoMetadata getMetadata();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_FFMPEGDATAVIDEO_H
