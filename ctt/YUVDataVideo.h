#if !defined(_YUVDATAVIDEO_H)
#define _YUVDATAVIDEO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Video.h"
#include "Frame.h"
#include "Memento.h"
#include "FileVideo.h"

namespace model {
namespace video {

/**
 * A Video read from a YUV 4:4:4 or YUV 4:2:2 video file.
 *
 */
class YUVDataVideo : public FileVideo {
public:
	/**
	* Creates a new YUVDataVideo representing the YUV 4:4:4 or YUV 4:2:2 video at the submitted location in the file system.
	* @param videoFile the path to the video file which will be loaded
	* @param metadataFile the path to the file containing the metadata for the video file
	* @param context the context in which the video creates its frames
	* @throws IOException if the file at the submitted location can't be accessed.
	* @throws InvalidArgumentException if the files at the submitted locations aren't valid YUV 4:4:4 or YUV 4:2:2 video or metadata files
	*/
	YUVDataVideo(QDir videoFile, QDir metadataFile, QOpenGLContext context);

	VideoMetadata getMetadata();

	Frame getFrame(int frameNumber);

	Memento getMemento();

	void restore(Memento memento);

    static Saveable* getDummy();

private:
	/**
	* Creates a dummy YUVDataVideo.
	*/
	YUVDataVideo();
};

}  // namespace video
}  // namespace model

#endif  //_YUVDATAVIDEO_H
