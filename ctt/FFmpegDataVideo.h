


#if !defined(_FFMPEGDATAVIDEO_H)
#define _FFMPEGDATAVIDEO_H

#include "DataVideo.h"
#include "Frame.h"
#include "Memento.h"

class FFmpegDataVideo : public DataVideo {
public:
	VideoMetadata getMetadata();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
};

#endif  //_FFMPEGDATAVIDEO_H
