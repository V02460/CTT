#ifndef _FFMPEGDATAVIDEO_H
#define _FFMPEGDATAVIDEO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDir>

#include "Video.h"
#include "Frame.h"
#include "Memento.h"
#include "FileVideo.h"

namespace model {
namespace video {

/**
 * A Video read from a mpeg-2, mpeg-4 part 2 or mpeg-4 part 10 video file.
 */
class FFmpegDataVideo : public FileVideo {
public:
    typedef QScopedPointer<FFmpegDataVideo> uptr;
    typedef QSharedPointer<FFmpegDataVideo> sptr;
    typedef QWeakPointer<FFmpegDataVideo> wptr;

    /**
     * Creates a new FFmpegDataVideo representing the mpeg-2, mpeg-4 part 2 or mpeg-4 part 10 video at the submitted
     * location in the file system.
     *
     * @param path the path to the video file which will be loaded
     * @param context the context in which the video creates its frames
     * @throws IOException if the file at the submitted location can't be accessed.
     * @throws InvalidArgumentException if the file at the submitted location isn't a valid mpeg-2, mpeg-4 part 2 or
     *     mpeg-4 part 10 video file
     */
    FFmpegDataVideo(QDir path, QSharedPointer<QOpenGLContext> context);

    VideoMetadata getMetadata() const;

	virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
};

}  // namespace video
}  // namespace model

#endif  //_FFMPEGDATAVIDEO_H
