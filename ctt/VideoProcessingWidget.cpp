#include "VideoProcessingWidget.h"
#include "Video.h"
#include "VideoFileType.h"

namespace view {

signal VideoProcessingWidget::videoForAnalysingAdded(Video video) {

}

signal VideoProcessingWidget::videoForAnalysingRemoved(Video video) {

}

signal VideoProcessingWidget::saveVideo(Video video, QDir path, VideoFileType fileType) {

}

}  // namespace view