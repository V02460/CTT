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
	slot writeVideo(Video video, QDir path, VideoFileType fileType);
};

}  // namespace video
}  // namespace model

#endif  //_VIDEOSAVERFACTORY_H
