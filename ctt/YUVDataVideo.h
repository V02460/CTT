#ifndef _YUVDATAVIDEO_H
#define _YUVDATAVIDEO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QFile>

#include "Video.h"
#include "Frame.h"
#include "Memento.h"
#include "FileVideo.h"
#include "YUVType.h"

using model::video::YUVType;

namespace model {
namespace video {

/**
 * A Video read from a YUV 4:4:4, YUV 4:2:2 or YUV 4:2:0 video file.
 *
 */
class YUVDataVideo : public FileVideo {
public:
    typedef QScopedPointer<YUVDataVideo> uptr;
    typedef QSharedPointer<YUVDataVideo> sptr;
    typedef QWeakPointer<YUVDataVideo> wptr;

    /**
    * Creates a new YUVDataVideo representing the YUV 4:4:4, YUV 4:2:2 or YUV 4:2:0 video at the submitted location in the file
    * system.
    *
    * @param pathToVideoFile the path to the video file which will be loaded
    * @param pathToMetadataFile the path to the file containing the metadata for the video file
    * @param context the context in which the video creates its frames
    * @throws FileNotFoundException if the files at the submitted locations can't be found.
    * @throws IllegalArgumentException if the files at the submitted locations aren't valid YUV 4:4:4, YUV 4:2:2 or 
    *     YUV 4:2:0 video or metadata files
	* @throws IllegalArgumentException if resolution has a size or width of 0
	* @throws IllegalArgumentException if framerate isn't greater than zero
    */
    YUVDataVideo(QString pathToVideoFile, QString pathToMetadataFile, QSize resolution, double framerate, YUVType type, QSharedPointer<QOpenGLContext> context);

    /**
     * Destructor of YUVDataVideo.
     */
    ~YUVDataVideo();

	virtual QList<Module*> getUsesList();

	virtual unsigned int getFrameCount();

	virtual bool uses(const model::Module &module);

    virtual VideoMetadata getMetadata() const;

    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;

private:
    /**
    * Creates a dummy YUVDataVideo.
    */
    YUVDataVideo();

	/**
	 * Loads numberOfFramesInMemory frames from the video file to the buffer, starting at the submitted startFrame.
	 * @param startFrame this is the first frame which will be loaded to the buffer
	 */
	void load(unsigned int startFrame) const;

	/**
	* Checks whether the frame with the submitted number is currently in the buffer
	* @return true only if the frame with the submitted number is currently in the buffer
	*/
	bool hasFrameInBuffer(unsigned int frameNr) const;

	static const unsigned int numberOfFramesInMemory = 10; /**< The size of the buffer in frames*/

	mutable QByteArray videoBuffer; /**< The buffer for the video data*/
	mutable unsigned int firstFrameInMemory; /**< The number of the first frame in the buffer*/

	unsigned int chromaSize; /**< The size of the U and V channels of each frame of the YUV file*/
	unsigned int pixelsPerFrame; /**< The number of pixels in each frame*/
	unsigned int bytesPerFrame; /**< The number of bytes for each frame*/
	QFile metadataFile; /**< The file the video reads its metadata from*/
	QDataStream metadataFileStream; /**< The file stream the video uses to read its metadata*/
	VideoMetadata metadata; /**< The metadata of the YUV video */
	QString pathToMetadataFile; /**< The metadata of the YUV video */
};

}  // namespace video
}  // namespace model

#endif  //_YUVDATAVIDEO_H
