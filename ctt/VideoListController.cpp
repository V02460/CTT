#include "VideoListController.h"
#include "FFmpegDataVideo.h"
#include "YUVDataVideo.h"
#include "FilteredVideo.h"
#include "GlobalContext.h"

#include "OperationList.h"
#include "VideoAddedOperation.h"
#include "VideoRemovedOperation.h"

#include "IllegalArgumentException.h"


namespace controller {

using ::model::saveable::SaveableList;
using ::model::video::Video;
using ::model::filter::FilteredVideo;
using ::model::video::FFmpegDataVideo;
using ::model::video::YUVDataVideo;
using ::model::GlobalContext;
using ::controller::operation::OperationList;
using ::controller::operation::Operation;
using ::controller::operation::VideoAddedOperation;
using ::controller::operation::VideoRemovedOperation;

VideoListController::VideoListController(SaveableList<FilteredVideo>::sptr videoList): videoList(videoList) {

}

void VideoListController::addVideo(QString path) {
	FFmpegDataVideo ffmpegVideo(path, GlobalContext::get());

	FilteredVideo::sptr video(new FilteredVideo(QSharedPointer<FFmpegDataVideo>(&ffmpegVideo)));
	
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoAddedOperation(video, videoList)));
}

void VideoListController::addVideo(QString path, int width, int height, double fps, YUVType type, unsigned int length) {
	YUVDataVideo yuvVideo(path, QSize(width, height), fps, type, GlobalContext::get());

	FilteredVideo::sptr video(new FilteredVideo(QSharedPointer<YUVDataVideo>(&yuvVideo)));

	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoAddedOperation(video, videoList)));
}

void VideoListController::addVideo(QString pathToVideoFile, QString pathToMetadataFile, int width, int height, double fps, YUVType type, unsigned int length) {
	YUVDataVideo yuvVideo(pathToVideoFile, pathToMetadataFile, QSize(width, height), fps, type, GlobalContext::get());

	FilteredVideo::sptr video(new FilteredVideo(QSharedPointer<YUVDataVideo>(&yuvVideo)));

	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoAddedOperation(video, videoList)));
}

void VideoListController::addVideo(FilteredVideo::sptr video) {
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoAddedOperation(video, videoList)));
}

void VideoListController::removeVideo(int index) {	
	if (index < 0 || index >= videoList->getSize()) {
		throw new exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
	}
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoRemovedOperation(index, videoList)));
}

void VideoListController::removeVideo(const FilteredVideo &video) {
	for (int i = 0; i < videoList->getSize(); i++) {
		if (&video == videoList->get(i).data()) {
			OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
				new VideoRemovedOperation(i, videoList)));
			return;
		}
		throw new exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
	}
}

}  // namespace controller