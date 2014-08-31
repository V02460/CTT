#ifndef _EXTENDEDVIDEOLISTCONTROLLER
#define _EXTENDEDVIDEOLISTCONTROLLER

#include "VideoListController.h"

#include "FilteredVideo.h"
#include "Player.h"

namespace controller {

class ExtendedVideoListController : public controller::VideoListController {
public:
	typedef QScopedPointer<VideoListController> uptr;
	typedef QSharedPointer<VideoListController> sptr;
	typedef QWeakPointer<VideoListController> wptr;

	ExtendedVideoListController(model::saveable::SaveableList<model::filter::FilteredVideo>::sptr baseVideos,
		model::saveable::SaveableList<model::filter::FilteredVideo>::sptr filteredVideos,
		model::saveable::SaveableList<model::player::Player>::sptr playerList);

public slots:
	virtual void addVideo(QString path);
	virtual void addVideo(QString path, int width, int height, double fps, model::video::YUVType type, unsigned int length);
	virtual void addVideo(model::filter::FilteredVideo::sptr video);
	virtual void removeVideo(int index);
	virtual void removeVideo(const model::filter::FilteredVideo &video);
//	virtual void addVideo(QString path, QString macrobockPath, int width, int height, double fps, model::video::YUVType type, unsigned int length);

private:
	model::saveable::SaveableList<model::filter::FilteredVideo>::sptr filteredVideos;
	model::saveable::SaveableList<model::player::Player>::sptr playerList;
};

} // namespace controller

#endif //_EXTENDEDVIDEOLISTCONTROLLER