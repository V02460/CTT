


#if !defined(_VIDEO_H)
#define _VIDEO_H

#include "Module.h"
#include "Frame.h"
#include "Memento.h"
#include "VideoMetadata.h"

class Video : public Module {
public:
	virtual VideoMetadata getMetadata() = 0;
	void save(Path path);
	Frame getScaledFrame(int frameNumber, int x, int y);
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
private:
	VideoMetadata *metadata;
};

#endif  //_VIDEO_H
