#if !defined(_HSLPIXELDIFF_H)
#define _HSLPIXELDIFF_H

#include "PixelDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

class HSLPixelDiff : public PixelDiff {
public:
	QOpenGLTexture getPixelDif(int frameNr);
	double getDif(int frameNr);
	void FrameDif(Video video1, Video video2);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace difference
}  // namespace model

#endif  //_HSLPIXELDIFF_H
