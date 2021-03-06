#ifndef _YUVDATAVIDEO_H
#define _YUVDATAVIDEO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QFile>
#include <QVector>
#include <QColor>

#include "Video.h"
#include "Frame.h"
#include "Memento.h"
#include "FileVideo.h"
#include "YUVType.h"

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
     * system. Assumes sdtv YUV colors.
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
     * system. Assumes sdtv YUV colors.
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
	* Creates a new YUVDataVideo representing the YUV 4:4:4, YUV 4:2:2 or YUV 4:2:0 video at the submitted location in the file
	* system.
	*
	* @param pathToVideoFile the path to the video file which will be loaded
	* @param resolution the resolution of the video
	* @param framerate the framerate of the video in fps
	* @param type specifies the YUV type of the video, i.e. 444, 422 or 420
	* @param isHDTV if this is true, HDTV YUV to RGB conversion is used
	* @param context the context in which the video creates its frames
	* @throws FileNotFoundException if the files at the submitted locations can't be found.
	* @throws IllegalArgumentException if the file at the submitted locations isn't a valid YUV 4:4:4, YUV 4:2:2 or
	*     YUV 4:2:0 video file
	* @throws IllegalArgumentException if resolution has a size or width of 0
	* @throws IllegalArgumentException if framerate isn't greater than zero
	*/
	YUVDataVideo(QString pathToVideoFile, QSize resolution, double framerate, YUVType type, bool isHDTV, QSharedPointer<QOpenGLContext> context);

	/**
	* Creates a new YUVDataVideo representing the YUV 4:4:4, YUV 4:2:2 or YUV 4:2:0 video at the submitted location in the file
	* system.
	*
	* @param pathToVideoFile the path to the video file which will be loaded
	* @param pathToMetadataFile the path to the file containing the metadata for the video file (only motion vectors apparently?)
	* @param resolution the resolution of the video
	* @param framerate the framerate of the video in fps
	* @param type specifies the YUV type of the video, i.e. 444, 422 or 420
	* @param isHDTV if this is true, HDTV YUV to RGB conversion is used
	* @param context the context in which the video creates its frames
	* @throws FileNotFoundException if the files at the submitted locations can't be found.
	* @throws IllegalArgumentException if the files at the submitted locations aren't valid YUV 4:4:4, YUV 4:2:2 or
	*     YUV 4:2:0 video or metadata files
	* @throws IllegalArgumentException if resolution has a height or width of 0
	* @throws IllegalArgumentException if framerate isn't greater than zero
	*/
	YUVDataVideo(QString pathToVideoFile, QString pathToMetadataFile, QSize resolution, double framerate, YUVType type, bool isHDTV, QSharedPointer<QOpenGLContext> context);

    /**
     * Destructor of YUVDataVideo.
     */
    ~YUVDataVideo();

	static ::model::saveable::Saveable::sptr YUVDataVideo::getDummy();

	virtual unsigned int getFrameCount() const Q_DECL_OVERRIDE;

    virtual VideoMetadata getMetadata() const Q_DECL_OVERRIDE;

    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;

    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;

	static Saveable::SaveableType getSaveableType();
	virtual SaveableType saveableType() const Q_DECL_OVERRIDE { return getSaveableType(); }

private:
    Q_DISABLE_COPY(YUVDataVideo)

	const static QString hasMetadataFileStringId;
	const static QString resXStringId;
	const static QString resYStringId;
	const static QString videoPathStringId;
	const static QString metadataPathStringId;
	const static QString framerateStringId;
	const static QString yuvTypeStringId;
	const static QString isHDTVStringId;

    /**
     * Creates a dummy YUVDataVideo.
     */
    YUVDataVideo();

	/**
	 * Loads numberOfFramesInMemory frames from the video file to the buffer, starting at the submitted startFrame.
     *
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

    /**
     * Get the number of frame which must be loaded for the given start frame.
     *
     * @param startFrame Used to calculate the number of frame which have to loaded when used this as start frame.
     */
    unsigned int getFramesToLoad(unsigned int startFrame) const;

	static const unsigned int kNumberOfFramesInMemory = 1; /**< The size of the buffer in frames*/

    mutable QVector<Surface::sptr> videoSurfaceBuffer; /**< Intermediate buffer for storing frames without metadata*/
	mutable QVector<::model::frame::Frame::sptr> videoBuffer; /**< The buffer for the video data*/
	mutable QVector<::model::frame::FrameMetadata::sptr> metadataBuffer; /**< The buffer for the metadata*/
	mutable unsigned int firstFrameInMemory; /**< The number of the first frame in the buffer*/

	unsigned int chromaSize; /**< The size of the U and V channels of each frame of the YUV file*/
	unsigned long long pixelsPerFrame; /**< The number of pixels in each frame*/
	unsigned long long bytesPerFrame; /**< The number of bytes for each frame*/
	mutable QFile metadataFile; /**< The file the video reads its metadata from*/
	VideoMetadata metadata; /**< The metadata of the YUV video */
	YUVType type; /**< The YUv type of the YUV video */

	bool hasMetadataFile; /**< Whether the video has a metadata file*/
	QString pathToMetadataFile; /**< The metadata file of the YUV video */

	bool isHDTV;
};

}  // namespace video
}  // namespace model

#endif  //_YUVDATAVIDEO_H
