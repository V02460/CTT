#include "ExtendedVideoListController.h"
#include "FFmpegDataVideo.h"
#include "YUVDataVideo.h"

#include "GlobalContext.h"

#include "Operation.h"
#include "OperationList.h"
#include "ExtendedVideoAddedOperation.h"
#include "ExtendedVideoRemovedOperation.h"

#include "IllegalArgumentException.h"


namespace controller {

	using ::model::saveable::SaveableList;
	using ::model::video::Video;
	using ::model::filter::FilteredVideo;
	using ::model::player::Player;
	using ::model::video::FFmpegDataVideo;
	using ::model::video::YUVDataVideo;
	using ::model::GlobalContext;
	using ::controller::operation::Operation;
	using ::controller::operation::OperationList;
	using ::controller::operation::ExtendedVideoAddedOperation;
	using ::controller::operation::ExtendedVideoRemovedOperation;

	ExtendedVideoListController::ExtendedVideoListController(SaveableList<FilteredVideo>::sptr baseVideos,
		SaveableList<FilteredVideo>::sptr filteredVideos,
		SaveableList<Player>::sptr player) : VideoListController(baseVideos), filteredVideos(filteredVideos), player(player){
	}

	void ExtendedVideoListController::addVideo(QString path) {

		QOpenGLContext context(GlobalContext::get().data());
		FFmpegDataVideo ffmpegVideo(path, QSharedPointer<QOpenGLContext>(&context));

		FilteredVideo::sptr video(new FilteredVideo(QSharedPointer<FFmpegDataVideo>(&ffmpegVideo)));
		FilteredVideo::sptr filteredVideo(new FilteredVideo(QSharedPointer<FFmpegDataVideo>(&ffmpegVideo)));

		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new ExtendedVideoAddedOperation(video, filteredVideo, videoList, filteredVideos)));
	}

	void ExtendedVideoListController::addVideo(QString path, int width, int height, double fps, model::video::YUVType type, unsigned int length) {
		QOpenGLContext context(GlobalContext::get().data());
		QSize resolution(QSize(width, height));
		YUVDataVideo yuvVideo(path, resolution, fps, type, QSharedPointer<QOpenGLContext>(&context));

		FilteredVideo::sptr video(new FilteredVideo(QSharedPointer<YUVDataVideo>(&yuvVideo)));		
		FilteredVideo::sptr filteredVideo(new FilteredVideo(QSharedPointer<YUVDataVideo>(&yuvVideo)));

		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new ExtendedVideoAddedOperation(video, filteredVideo, videoList, filteredVideos)));
	}

	void ExtendedVideoListController::addVideo(FilteredVideo::sptr video) {
		FilteredVideo::sptr filteredVideo(new FilteredVideo(video));
		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new ExtendedVideoAddedOperation(video, filteredVideo, videoList, filteredVideos)));
	}

	void ExtendedVideoListController::removeVideo(int index) {
		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new ExtendedVideoRemovedOperation(index, videoList, filteredVideos)));
	}

	void ExtendedVideoListController::removeVideo(const FilteredVideo &baseVideo) {
		for (int i = 0; i < videoList->getSize(); i++) {
			if (&baseVideo == videoList->get(i).data()) {
				OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
					new ExtendedVideoRemovedOperation(i, videoList, filteredVideos)));
				return;
			}
			throw new exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
		}
	}

}  // namespace controller