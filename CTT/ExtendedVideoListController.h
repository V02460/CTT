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
		void addVideo(QString path);
		void addVideo(QString path, int width, int height, double fps, model::video::YUVType type, unsigned int length);
		void addVideo(QString pathToVideoFile, QString pathToMetadataFile, int width, int height, double fps, model::video::YUVType type, unsigned int length);
		void addVideo(model::filter::FilteredVideo::sptr video);
		void removeVideo(int index);
		void removeVideo(const model::filter::FilteredVideo &video);

	private:
		model::saveable::SaveableList<model::filter::FilteredVideo>::sptr filteredVideos;
		model::saveable::SaveableList<model::player::Player>::sptr playerList;
	};
}

#endif //_EXTENDEDVIDEOLISTCONTROLLER