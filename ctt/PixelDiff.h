#if !defined(_PIXELDIFF_H)
#define _PIXELDIFF_H

#include "FrameDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

class PixelDiff : public FrameDiff {
public:
	virtual QOpenGLTexture getPixelDif(int frameNr) = 0;
	double getDif(int frameNr);
	void FrameDif(Video video1, Video video2);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace difference
}  // namespace model

#endif  //_PIXELDIFF_H
