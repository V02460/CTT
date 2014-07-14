#ifndef _VIDEOSAVER_H
#define _VIDEOSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Video.h"
#include "VideoFileType.h"

namespace model {
namespace video {

/**
 * Saves videos as videofiles in the filesystem.
 */
class VideoSaver {
public:
    typedef QScopedPointer<VideoSaver> uptr;
    typedef QSharedPointer<VideoSaver> sptr;
    typedef QWeakPointer<VideoSaver> wptr;

    /**
     * Saves the submitted video as a videofile of the submitted type to the submitted path in the filesystem.
     *
     * @param video the video the saver will save
     * @param path the path to the location the videofile will be written to
     * @param type the type of the videofile that will be saved
     * @throws IOException if the videofile can't be written to the location specified in path
     */
    static void writeToFile(Video video, QDir path, VideoFileType type);

	/**
	 *	Converts a given VideoFileType to a QString representing the suffix of the file.
	 *
	 *	@param fileType The VideoFileType to be converted.
	 *
	 *	@return The suffix for a file.
	 *
	 *	@throws IllegalArgumentException if this file type doesn't exist.
	 */
	static QString convertVideoFileTypeToString(VideoFileType fileType);

	/**
	*	Converts a given QString representing the file's suffix to the corresponding VideoFileType.
	*
	*	@param suffix The suffix to be converted.
	*
	*	@return The VideoFileType belonging to the given suffix.
	*
	*	@throws IllegalArgumentException if the file type for this suffix isn't supported.
	*/
	static VideoFileType convertStringToVideoFileType(QString suffix);

private:
    VideoSaver();
};

}  // namespace video
}  // namespace model

#endif  //_VIDEOSAVER_H
