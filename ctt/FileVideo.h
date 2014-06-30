#pragma once
#include "Video.h"

/**
 * A Video read from a video file.
 */
class FileVideo :
	public Video
{
public:
	typedef QScopedPointer<FileVideo> uptr;
	typedef QSharedPointer<FileVideo> sptr;
	typedef QWeakPointer<FileVideo> wptr;

	VideoMetadata getMetadata();

	virtual Frame getFrame(int frameNumber);

	virtual Memento getMemento();

	virtual void restore(Memento memento);

	/**
	* Returns the path to the video file this Video loads its frames from.
	* @return QDir the path to the video file this Video loads its frames from
	*/
	QDir getPath();

protected:
	QDir path; /**< the path to the video file this Video loads its frames from. */
	VideoMetadata metadata; /**< metadata valid for the whole video. */
	QOpenGLContext context; /**< The QOpenGLContext in which the Video creates its frames.*/
};

