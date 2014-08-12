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
using model::saveable::Memento;

namespace model {
namespace video {

/**
 * A Video read from a YUV 4:4:4, YUV 4:2:2 or YUV 4:2:0 video file.
 *
 */
class YUVDataVideo : public FileVideo {
public:
	Q_DISABLE_COPY(YUVDataVideo)

    typedef QScopedPointer<YUVDataVideo> uptr;
    typedef QSharedPointer<YUVDataVideo> sptr;
    typedef QWeakPointer<YUVDataVideo> wptr;

    /**
    * Creates a new YUVDataVideo representing the YUV 4:4:4, YUV 4:2:2 or YUV 4:2:0 video at the submitted location in the file
    * system.
    *
    * @param pathToVideoFile the path to the video file which will be loaded
    * @param pathToMetadataFile the path to the file containing the metadata for the video file (only motion vectors apparently?)
	* @param resolution the resolution of the video
	* @param framerate the framerate of the video in fps
	* @param type specifies the YUV type of the video, i.e. 444, 422 or 420
    * @param context the context in which the video creates its frames
    * @throws FileNotFoundException if the files at the submitted locations can't be found.
    * @throws IllegalArgumentException if the files at the submitted locations aren't valid YUV 4:4:4, YUV 4:2:2 or 
    *     YUV 4:2:0 video or metadata files
	* @throws IllegalArgumentException if resolution has a height or width of 0
	* @throws IllegalArgumentException if framerate isn't greater than zero
    */
    YUVDataVideo(QString pathToVideoFile, QString pathToMetadataFile, QSize resolution, double framerate, YUVType type, QSharedPointer<QOpenGLContext> context);

	/**
	* Creates a new YUVDataVideo representing the YUV 4:4:4, YUV 4:2:2 or YUV 4:2:0 video at the submitted location in the file
	* system.
	*
	* @param pathToVideoFile the path to the video file which will be loaded
	* @param resolution the resolution of the video
	* @param framerate the framerate of the video in fps
	* @param type specifies the YUV type of the video, i.e. 444, 422 or 420
	* @param context the context in which the video creates its frames
	* @throws FileNotFoundException if the files at the submitted locations can't be found.
	* @throws IllegalArgumentException if the file at the submitted locations isn't a valid YUV 4:4:4, YUV 4:2:2 or
	*     YUV 4:2:0 video file
	* @throws IllegalArgumentException if resolution has a size or width of 0
	* @throws IllegalArgumentException if framerate isn't greater than zero
	*/
	YUVDataVideo(QString pathToVideoFile, QSize resolution, double framerate, YUVType type, QSharedPointer<QOpenGLContext> context);

    /**
     * Destructor of YUVDataVideo.
     */
    ~YUVDataVideo();

	static ::model::saveable::Saveable::sptr YUVDataVideo::getDummy();

	virtual QList<const Module*> getUsesList() const;

	virtual unsigned int getFrameCount() const;

	virtual bool uses(const model::Module &module) const;

    virtual VideoMetadata getMetadata() const;

    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;

	virtual Memento getMemento() const;

	virtual void restore(Memento memento);

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

	void loadVideodata(unsigned int startFrame) const;

	void loadMetadata(unsigned int startFrame) const;

	/**
	* Checks whether the frame with the submitted number is currently in the buffer
	* @return true only if the frame with the submitted number is currently in the buffer
	*/
	bool hasFrameInBuffer(unsigned int frameNr) const;

	static const unsigned int numberOfFramesInMemory = 10; /**< The size of the buffer in frames*/

	mutable QByteArray videoBuffer; /**< The buffer for the video data*/
	mutable QByteArray metadataBuffer; /**< The buffer for the metadata*/
	mutable unsigned int firstFrameInMemory; /**< The number of the first frame in the buffer*/

	unsigned int chromaSize; /**< The size of the U and V channels of each frame of the YUV file*/
	unsigned int pixelsPerFrame; /**< The number of pixels in each frame*/
	unsigned int bytesPerFrame; /**< The number of bytes for each frame*/
	mutable QFile metadataFile; /**< The file the video reads its metadata from*/
	VideoMetadata metadata; /**< The metadata of the YUV video */

	bool hasMetadataFile; /**< Whether the video has a metadata file*/
	QString pathToMetadataFile; /**< The metadata file of the YUV video */

};

}  // namespace video
}  // namespace model

#endif  //_YUVDATAVIDEO_H
