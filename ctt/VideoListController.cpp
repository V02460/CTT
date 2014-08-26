#include "VideoListController.h"
#include "FFmpegDataVideo.h"
#include "YUVDataVideo.h"

#include "IllegalArgumentException.h"


namespace controller {

using ::model::saveable::SaveableList;
using ::model::video::Video;
using ::model::video::FFmpegDataVideo;
using ::model::video::YUVDataVideo;


VideoListController::VideoListController(SaveableList<Video>::sptr videoList): videoList(videoList) {

}

void VideoListController::addVideo(QString path) {
	//new context??
	QOpenGLContext context(new QOpenGLContext());
	FFmpegDataVideo video(path, QSharedPointer<QOpenGLContext>(&context));	
	videoList->insert(videoList->getSize(), QSharedPointer<FFmpegDataVideo>(&video));
}

void VideoListController::addVideo(QString path, int width, int height, double fps, YUVType type, unsigned int length) {
	QOpenGLContext context(new QOpenGLContext());
	QSize resolution(QSize(width, height));
	YUVDataVideo video(path, resolution, fps, type, QSharedPointer<QOpenGLContext>(&context));
	videoList->insert(videoList->getSize(), QSharedPointer<YUVDataVideo>(&video));
}

void VideoListController::addVideo(Video::sptr video) {
	videoList->insert(videoList->getSize(), video);
}

void VideoListController::removeVideo(int index) {	
	videoList->remove(index);
}

void VideoListController::removeVideo(const Video &video) {
	for (int i = 0; i < videoList->getSize(); i++) {
		if (&video == videoList->get(i).data()) {
			removeVideo(i);
			return;
		}
		throw new exception::IllegalArgumentException("The Video which is to be removed is not part of this VideoList.");
	}
}

}  // namespace controller