


#if !defined(_VIDEOPROCESSINGWIDGET_H)
#define _VIDEOPROCESSINGWIDGET_H

#include "Video.h"
#include "VideoFileType.h"
#include "VideoWidget.h"

class VideoProcessingWidget {
public:
	signal videoForAnalysingAdded(Video video);
	signal videoForAnalysingRemoved(Video video);
	signal saveVideo(Video video, QDir path, VideoFileType fileType);
private:
	bool showSaveButton;
	QCheckBox checkboxUseForAnalysis;
	QPushButton btnSaveVideo;
	VideoWidget *videoWidget;
};

#endif  //_VIDEOPROCESSINGWIDGET_H
