#ifndef _VIDEOLISTCONTROLLER_H
#define _VIDEOLISTCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QObject>

#include "Observer.h"
#include "Video.h"
#include "SaveableList.h"
#include "FileVideo.h"
#include "FilteredVideo.h"

namespace controller {

/**
 * The VideoListController manages requests to manipulate the VideoList.
 */
class VideoListController : public QObject {
    Q_OBJECT
public:
    typedef QScopedPointer<VideoListController> uptr;
    typedef QSharedPointer<VideoListController> sptr;
    typedef QWeakPointer<VideoListController> wptr;

    /**
     * Takes a video list and manages requests for it.
     *
     * @param videoList The list the controller will manage
     */
    VideoListController(::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList);

public slots:

    /**
     * Initiates adding a video, typically FFMPEG, to the VideoList.
     * Is called when a notification is received that a video should be added to the VideoList.
     *
     * @param path The path to the video which is to be added.
     */
    virtual void addVideo(QString path);

	/**
	* Initiates adding a video, typically YUV with metadata provided by the user, to the VideoList.
	* Is called when a notification is received that a video should be added to the VideoList.
	*
	* @param path The path to the video which is to be added.
	*/
	virtual void addVideo(QString path, int width, int height, double fps, model::video::YUVType type);

	/**
	* Initiates adding a video, typically YUV with metadata provided by the user, to the VideoList.
	* Is called when a notification is received that a video should be added to the VideoList.
	*
	* @param path The path to the video which is to be added.
	*/
	virtual void addVideo(QString pathToVideoFile, QString pathToMetaDataFile, int width, int height, double fps, model::video::YUVType type);

	/**
     * Initiates adding a video to the VideoList.
     * Is called when a notification is received that a video should be added to the VideoList.
     *
     * @param video The video which is to be added.
     */
	virtual void addVideo(::model::video::Video::sptr video);

    /**
    * Initiates removing a video from the VideoList.
    * Is called when a notification is received that a video should be removed from the VideoList.
    *
    * @param index The index of the video which is to be removed.
    **/
	virtual void removeVideo(int index);
    
    /**
    * Initiates removing a video from the VideoList.
    * Is called when a notification is received that a video should be removed from the VideoList.
    *
    * @param video The video which is to be removed.
    **/
	virtual void removeVideo(const ::model::video::Video &video);

//	virtual void addVideo(QString path, QString macrobockPath, int width, int height, double fps, model::video::YUVType type, unsigned int length);

protected:
	model::saveable::SaveableList<model::filter::FilteredVideo>::sptr videoList;
};

}  // namespace controller

#endif  //_VIDEOLISTCONTROLLER_H
