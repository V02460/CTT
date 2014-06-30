#if !defined(_VIDEO_H)
#define _VIDEO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Module.h"
#include "Frame.h"
#include "Memento.h"
#include "VideoMetadata.h"
#include "VideoFileType.h"
#include <QDir>

namespace model {
namespace video {

/**
 * Represents a video with all it's frames and metadata.
 *
 */
class Video : public Module {
public:
	typedef QScopedPointer<Video> uptr;
	typedef QSharedPointer<Video> sptr;
	typedef QWeakPointer<Video> wptr;

    /**
     * Gets the metadata of the Video which are valid for the whole video and not just specific frames
     *
     * @return VideoMetadata the metadata of the Video which are valid for the whole video and not just specific frames
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual model::video::VideoMetadata getMetadata() const = 0;

    /**
     * Saves the Video to the submitted path in the filesystem
     *
     * @param path the path to where the video will be saved
     * @param fileType the file type in which the video will be saved
     * @throws IOException if it's not possible to save the video to the submitted path
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    void save(QDir path, model::video::VideoFileType fileType);

    /**
     * Gets the frame with the submitted number scaled to the submitted resolution.
     * Rescaling will use bicubic interpolation.
     *
     * @param frameNumber the number of the frame which will be returned
     * @param size the size of the frame which will be returned
     * @return Frame the scaled Frame
	 * @throws IllegalStateException if the the method was called on a dummy
     */
    virtual frame::Frame getScaledFrame(unsigned int frameNumber, QSize size) const;

	/**
	 * Returns the QOpenGLContext in which the Video creates its frames.
	 * @return QOpenGLContext the QOpenGLContext in which the Video creates its frames
	 */
	QSharedPointer<QOpenGLContext> getContext() const;

    virtual frame::Frame getFrame(unsigned int frameNumber) = 0;
};

}  // namespace video
}  // namespace model

#endif  //_VIDEO_H
