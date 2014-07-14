#include "VideoSaver.h"

namespace model {
namespace video {
	void VideoSaver::writeToFile(Video &video, QDir path, VideoFileType type) {
		
	}

	QString VideoSaver::convertVideoFileTypeToString(VideoFileType fileType) {
		return *new QString("");
	}

	VideoFileType VideoSaver::convertStringToVideoFileType(QString suffix) {
		return VideoFileType::YUV;
	}
} // namespace video
} // namespace model