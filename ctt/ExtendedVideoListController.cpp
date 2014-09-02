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
                                                         SaveableList<Player>::sptr playerList)
        : VideoListController(baseVideos)
        , filteredVideos(filteredVideos)
        , playerList(playerList) {
}

void ExtendedVideoListController::addVideo(QString path) {

    FFmpegDataVideo::sptr ffmpegVideo(new FFmpegDataVideo(path, GlobalContext::get()));

    FilteredVideo::sptr video(new FilteredVideo(ffmpegVideo));
    FilteredVideo::sptr filteredVideo(new FilteredVideo(ffmpegVideo));

    OperationList::getInstance()->doOperation(
        Operation::sptr(new ExtendedVideoAddedOperation(playerList,  video, filteredVideo, videoList, filteredVideos)));

}

void ExtendedVideoListController::addVideo(QString path,
                                           int width,
                                           int height,
                                           double fps,
                                           YUVType type,
                                           unsigned int length) {

    YUVDataVideo::sptr yuvVideo(new YUVDataVideo(path, QSize(width, height), fps, type, GlobalContext::get()));

    FilteredVideo::sptr video(new FilteredVideo(yuvVideo));
    FilteredVideo::sptr filteredVideo(new FilteredVideo(yuvVideo));

    OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
        new ExtendedVideoAddedOperation(playerList, video, filteredVideo, videoList, filteredVideos)));
}

void ExtendedVideoListController::addVideo(QString pathToVideoFile,
                                           QString pathToMetadataFile,
                                           int width,
                                           int height,
                                           double fps,
                                           YUVType type,
                                           unsigned int length) {

    YUVDataVideo::sptr yuvVideo(new YUVDataVideo(pathToVideoFile,
                                                 pathToMetadataFile,
                                                 QSize(width, height),
                                                 fps,
                                                 type,
                                                 GlobalContext::get()));

    FilteredVideo::sptr video(new FilteredVideo(yuvVideo));
    FilteredVideo::sptr filteredVideo(new FilteredVideo(yuvVideo));


    OperationList::getInstance()->doOperation(
        Operation::sptr(new ExtendedVideoAddedOperation(playerList, video, filteredVideo, videoList, filteredVideos)));
}

void ExtendedVideoListController::addVideo(FilteredVideo::sptr video) {
    // don't add a video twice
    for (int i = 0; i < videoList->getSize(); i++) {
        if (videoList->get(i)->getBaseVideo() == video) {
            return;
        }
    }

    // TODO: is this intentional?
    FilteredVideo::sptr video1(new FilteredVideo(video));
    FilteredVideo::sptr video2(new FilteredVideo(video));
    OperationList::getInstance()->doOperation(
        Operation::sptr(new ExtendedVideoAddedOperation(playerList, video1, video2, videoList, filteredVideos)));
}

void ExtendedVideoListController::removeVideo(int index) {
    OperationList::getInstance()->doOperation(
        Operation::sptr(new ExtendedVideoRemovedOperation(index, videoList, filteredVideos)));
}

void ExtendedVideoListController::removeVideo(const FilteredVideo &baseVideo) {
    for (int i = 0; i < videoList->getSize(); i++) {
        if (&baseVideo == videoList->get(i).data()) {
            OperationList::getInstance()->doOperation(
            Operation::sptr(new ExtendedVideoRemovedOperation(i, videoList, filteredVideos)));
            return;
        }
    }

    throw exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
}

}  // namespace controller