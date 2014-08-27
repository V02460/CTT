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

    /**
    * Returns the path to the video file this Video loads its frames from.
    *
    * @return QDir the path to the video file this Video loads its frames from
	* @throws IllegalStateException if the method is called on a dummy
    */
    QString getPath() const;

	virtual QList<const Module*> getUsesList() const;

	virtual bool uses(const model::Module &module) const;

	virtual QSharedPointer<QOpenGLContext> getContext() const ;

    static ::model::saveable::Saveable::SaveableType getSaveableType();

protected:
	/**
	 * Creates a File video initialized with the submitted path and context.
	 * @param path the path to the video file
	 * @param context the context in which the video creates it's frame
	 * @throws FileNotFoundException if the file at the submitted location can't be found
	 */
	FileVideo(QString path, QSharedPointer<QOpenGLContext> context);

	mutable QFile videoFile; /**< The Video File this Video loads its frames from*/
    QString pathToVideoFile; /**< the path to the video file this Video loads its frames from. */
    VideoMetadata::uptr metadata; /**< metadata valid for the whole video. */
    QSharedPointer<QOpenGLContext> context; /**< The QOpenGLContext in which the Video creates its frames.*/
	FileVideo();
};

}  // namespace video
}  // namespace model

#endif  //_FILEVIDEO_H