


#if !defined(_YUVPIXELDIFF_H)
#define _YUVPIXELDIFF_H

#include "PixelDiff.h"
#include "Video.h"
#include "Memento.h"

class YUVPixelDiff : public PixelDiff {
public:
	QOpenGLTexture getPixelDif(int frameNr);
	double getDif(int frameNr);
	void FrameDif(Video video1, Video video2);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_YUVPIXELDIFF_H
