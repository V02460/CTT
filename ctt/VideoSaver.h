#if !defined(_VIDEOSAVER_H)
#define _VIDEOSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Video.h"

namespace model {
namespace video {

class VideoSaver {
public:
	typedef QScopedPointer<VideoSaver> uptr;
	typedef QSharedPointer<VideoSaver> sptr;
	typedef QWeakPointer<VideoSaver> wptr;

	virtual void writeToFile(Video video, QDir path) = 0;
};

}  // namespace video
}  // namespace model

#endif  //_VIDEOSAVER_H
