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

VideoListController::VideoListController(SaveableList<FilteredVideo>::sptr videoList) : videoList(videoList) {
}

void VideoListController::addVideo(QString path) {
	FilteredVideo::sptr video(new FilteredVideo(QSharedPointer<FFmpegDataVideo>(new FFmpegDataVideo(path, GlobalContext::get()))));
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoAddedOperation(video, videoList)));
}

void VideoListController::addVideo(QString path, int width, int height, double fps, YUVType type, unsigned int length) {
	FilteredVideo::sptr video(new FilteredVideo(QSharedPointer<YUVDataVideo>(new YUVDataVideo(path, QSize(width, height), fps, type, GlobalContext::get()))));
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoAddedOperation(video, videoList)));
}

void VideoListController::addVideo(QString pathToVideoFile, QString pathToMetadataFile, int width, int height, double fps, YUVType type, unsigned int length) {
	FilteredVideo::sptr video(new FilteredVideo(QSharedPointer<YUVDataVideo>(new YUVDataVideo(pathToVideoFile, pathToMetadataFile, QSize(width, height), fps, type, GlobalContext::get()))));
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoAddedOperation(video, videoList)));
}

void VideoListController::addVideo(FilteredVideo::sptr video) {
	for (int i = 0; i < videoList->getSize(); i++) {
		if (videoList->get(i)->getBaseVideo() == video) return;
	}
	FilteredVideo::sptr filteredVideo(new FilteredVideo(video));
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new VideoAddedOperation(filteredVideo, videoList)));
}

void VideoListController::removeVideo(int index) {	
	if (index < 0 || index >= videoList->getSize()) {
		throw exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
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
		throw exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
	}
}

}  // namespace controller