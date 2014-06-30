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

class HSLPixelDiff : public PixelDiff {
public:
	typedef QScopedPointer<HSLPixelDiff> uptr;
	typedef QSharedPointer<HSLPixelDiff> sptr;
	typedef QWeakPointer<HSLPixelDiff> wptr;

	HSLPixelDiff(const video::Video &video1, const video::Video &video2);
	~HSLPixelDiff();

	virtual Surface getPixelDiff(unsigned int frameNr) const;
	virtual double getDiff(unsigned int frameNr) const;
};

}  // namespace difference
}  // namespace model

#endif  //_HSLPIXELDIFF_H
