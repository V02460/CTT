#if !defined(_HSLPIXELDIFF_H)
#define _HSLPIXELDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "PixelDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

/**
 * Calculates the distances in the HSL-colorspace between frames for every pair of corresponding pixels, and is able to normalize the resulting matrix if required.
 */
class HSLPixelDiff : public PixelDiff {
public:
	typedef QScopedPointer<HSLPixelDiff> uptr;
	typedef QSharedPointer<HSLPixelDiff> sptr;
	typedef QWeakPointer<HSLPixelDiff> wptr;

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
