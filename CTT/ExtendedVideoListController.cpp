#include "ExtendedVideoListController.h"
#include "FFmpegDataVideo.h"
#include "YUVDataVideo.h"

#include "IllegalArgumentException.h"


namespace controller {

	using ::model::saveable::SaveableList;
	using ::model::video::Video;
	using ::model::filter::FilteredVideo;
	using ::model::player::Player;
	using ::model::video::FFmpegDataVideo;
	using ::model::video::YUVDataVideo;

	ExtendedVideoListController::ExtendedVideoListController(SaveableList<Video>::sptr baseVideos,
		SaveableList<FilteredVideo>::sptr filteredVideos,
		SaveableList<Player>::sptr player) : VideoListController(baseVideos), filteredVideos(filteredVideos), player(player){
	}

	void ExtendedVideoListController::addVideo(QString path) {
		QOpenGLContext context(new QOpenGLContext());
		FFmpegDataVideo video(path, QSharedPointer<QOpenGLContext>(&context));
		videoList->insert(videoList->getSize(), QSharedPointer<FFmpegDataVideo>(&video));

		FilteredVideo::sptr filteredVideo(new FilteredVideo(QSharedPointer<FFmpegDataVideo>(&video)));
		filteredVideos->insert(filteredVideos->getSize(), filteredVideo);
	}

	void ExtendedVideoListController::addVideo(QString path, int width, int height, double fps, model::video::YUVType type, unsigned int length) {
		QOpenGLContext context(new QOpenGLContext());
		QSize resolution(QSize(width, height));
		YUVDataVideo video(path, resolution, fps, type, QSharedPointer<QOpenGLContext>(&context));
		videoList->insert(videoList->getSize(), QSharedPointer<YUVDataVideo>(&video));
		
		FilteredVideo::sptr filteredVideo(new FilteredVideo(QSharedPointer<YUVDataVideo>(&video)));
		filteredVideos->insert(filteredVideos->getSize(), filteredVideo);
	}

	void ExtendedVideoListController::addVideo(Video::sptr video) {
		videoList->insert(videoList->getSize(), video);
		FilteredVideo::sptr filteredVideo(new FilteredVideo(video));
		filteredVideos->insert(filteredVideos->getSize(), filteredVideo);
	}

	void ExtendedVideoListController::removeVideo(int index) {
		videoList->remove(index);
	}

	void ExtendedVideoListController::removeVideo(const Video &video) {
		for (int i = 0; i < videoList->getSize(); i++) {
			if (&video == videoList->get(i).data()) {
				removeVideo(i);
				return;
			}
			throw new exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
		}
	}

}  // namespace controller