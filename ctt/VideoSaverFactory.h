#if !defined(_VIDEOSAVERFACTORY_H)
#define _VIDEOSAVERFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Video.h"
#include "VideoFileType.h"

namespace model {
namespace video {

class VideoSaverFactory {
public:
	typedef QScopedPointer<VideoSaverFactory> uptr;
	typedef QSharedPointer<VideoSaverFactory> sptr;
	typedef QWeakPointer<VideoSaverFactory> wptr;

	slot writeVideo(Video video, QDir path, VideoFileType fileType);
};

}  // namespace video
}  // namespace model

#endif  //_VIDEOSAVERFACTORY_H
