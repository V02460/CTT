


#if !defined(_THUMBNAILLISTWIDGET_H)
#define _THUMBNAILLISTWIDGET_H

#include "Observer.h"

class ThumbnailListWidget : public Observer {
public:
	void ThumbnailListWidget(SaveableList<Video> filteredVideos, int selectableCount);
	signal videoAdded(QDir path);
	signal videoRemoved(int index);
private:
	List<QPushButton> thumbnailList;
	QPushButton btnAddVideo;
	SaveableList<Video> filteredVideos;
};

#endif  //_THUMBNAILLISTWIDGET_H
