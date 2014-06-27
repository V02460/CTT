


#if !defined(_HSLPIXELDIFF_H)
#define _HSLPIXELDIFF_H

#include "PixelDiff.h"
#include "Video.h"
#include "Memento.h"

class HSLPixelDiff : public PixelDiff {
public:
	QOpenGLTexture getPixelDif(int frameNr);
	double getDif(int frameNr);
	void FrameDif(Video video1, Video video2);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
};

#endif  //_HSLPIXELDIFF_H
