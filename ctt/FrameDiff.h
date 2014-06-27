


#if !defined(_FRAMEDIFF_H)
#define _FRAMEDIFF_H

#include "Savable.h"
#include "Video.h"
#include "Memento.h"

class FrameDiff : public Savable {
public:
	virtual double getDif(int frameNr) = 0;
	virtual void FrameDif(Video video1, Video video2) = 0;
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
private:
	Video video1;
	Video video2;
};

#endif  //_FRAMEDIFF_H
