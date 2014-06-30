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

/**
 * Calculates the distances in the YUV-colorspace between frames for every pair of corresponding pixels, and is able to
 * normalize the resulting matrix if required.
 */
class YUVPixelDiff : public PixelDiff {
public:
	typedef QScopedPointer<YUVPixelDiff> uptr;
	typedef QSharedPointer<YUVPixelDiff> sptr;
	typedef QWeakPointer<YUVPixelDiff> wptr;

	/**
	* Creates a new YUVPixelDiff comparing the two submitted videos.
	*
	* @param video1 the first of the two videos which will be compared
	* @param video1 the second of the two videos which will be compared
	* @throws InvalidArgumentException if the submitted videos don't create their frames in the same OpenGLContext
	*/
	YUVPixelDiff(video::Video::sptr video1, video::Video::sptr video2);
	virtual ~YUVPixelDiff();

	virtual Surface getPixelDiff(unsigned int frameNr) const;
	virtual double getDiff(unsigned int frameNr) const;
};

}  // namespace difference
}  // namespace model

#endif  //_YUVPIXELDIFF_H
