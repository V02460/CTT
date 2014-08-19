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

		ExtendedVideoListController(model::saveable::SaveableList<model::video::Video>::sptr baseVideos,
			model::saveable::SaveableList<model::filter::FilteredVideo>::sptr filteredVideos,
			model::saveable::SaveableList<model::player::Player>::sptr player);

	public slots:
		void addVideo(QString path);
		void addVideo(model::video::Video::sptr video);
		void removeVideo(int index);
		void removeVideo(const model::video::Video &video);

	private:
		model::saveable::SaveableList<model::filter::FilteredVideo>::sptr filteredVideos;
		model::saveable::SaveableList<model::player::Player>::sptr player;
	};
}

#endif //_EXTENDEDVIDEOLISTCONTROLLER