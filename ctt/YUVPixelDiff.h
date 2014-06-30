#if !defined(_YUVPIXELDIFF_H)
#define _YUVPIXELDIFF_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "PixelDiff.h"
#include "Video.h"
#include "Memento.h"

namespace model {
namespace difference {

class YUVPixelDiff : public PixelDiff {
public:
	typedef QScopedPointer<YUVPixelDiff> uptr;
	typedef QSharedPointer<YUVPixelDiff> sptr;
	typedef QWeakPointer<YUVPixelDiff> wptr;

	QOpenGLTexture getPixelDif(int frameNr);
	double getDif(int frameNr);
	void FrameDif(Video video1, Video video2);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace difference
}  // namespace model

#endif  //_YUVPIXELDIFF_H
