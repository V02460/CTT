#ifndef _FILEVIDEO_H
#define _FILEVIDEO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDir>

#include "Video.h"

namespace model {
namespace video {

/**
 * A Video read from a video file.
 */
class FileVideo : public Video
{
public:
    typedef QScopedPointer<FileVideo> uptr;
    typedef QSharedPointer<FileVideo> sptr;
    typedef QWeakPointer<FileVideo> wptr;

    FileVideo(QDir path);

    /**
    * Returns the path to the video file this Video loads its frames from.
    *
    * @return QDir the path to the video file this Video loads its frames from
    */
    QDir getPath() const;

protected:
    QDir path; /**< the path to the video file this Video loads its frames from. */
    VideoMetadata::uptr metadata; /**< metadata valid for the whole video. */
    QScopedPointer<QOpenGLContext> context; /**< The QOpenGLContext in which the Video creates its frames.*/
};

}  // namespace video
}  // namespace model

#endif  //_FILEVIDEO_H