#if !defined(_YUVVIDEOSAVER_H)
#define _YUVVIDEOSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace video {

#include "VideoSaver.h"
#include "Video.h"

class YUVVideoSaver : public VideoSaver {
public:
	typedef QScopedPointer<YUVVideoSaver> uptr;
	typedef QSharedPointer<YUVVideoSaver> sptr;
	typedef QWeakPointer<YUVVideoSaver> wptr;

	void writeToFile(Video video, QDir path);
};

}  // namespace video
}  // namespace model

#endif  //_YUVVIDEOSAVER_H
