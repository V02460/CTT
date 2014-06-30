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

	YUVPixelDiff(const video::Video &video1, const video::Video &video2);
	virtual ~YUVPixelDiff();

	virtual Surface getPixelDiff(unsigned int frameNr) const;
	virtual double getDiff(unsigned int frameNr) const;
};

}  // namespace difference
}  // namespace model

#endif  //_YUVPIXELDIFF_H
