


#if !defined(_THUMBNAILLISTWIDGET_H)
#define _THUMBNAILLISTWIDGET_H

#include "Observer.h"
#include "Video.h"
#include <QWidget>
#include <QPushButton>
#include <QList>
#include <QDir>

/**
 *	The TumbnailListWidget displays a set of videos by its thumbnails and provides the interactiable components to set one or more videos
 *	active, to add videos to and to remove videos from the program.
 */
class ThumbnailListWidget : public Observer, public QWidget {
public:
	/**
	 *	Creates a new TumbnailListWidget with a SavableList of filteredVideos which is diplayed by this widget.
	 *	The ThumbnailListWidget registers itself at the SaveableList to get notified, when the currently managed videos change.
	 *
	 *	@param filteredVideos The list of videos which should be displayed by this widget.
	 *	@param selectableCount The number of video which can be activated simultaniously.
	 */
	ThumbnailListWidget(SaveableList<Video> filteredVideos, int selectableCount);
signals:
	/**
	 *	This signal is emitted when a new video is added to the program.
	 *
	 *	@param path The file path that leads to the video file.
	 */
	void videoAdded(QDir path);
	/**
	 *	This signal is emitted when an exisitng video is removed from the program.
	 *
	 *	@param index The index in the filteredVideos list of the video which should be removed.
	 */
	void videoRemoved(int index);
private:
	QList<QPushButton> thumbnailList; /**< The list of buttons with the thumbnails of the specific videos as icons */
	QPushButton btnAddVideo; /**< The button to add a new video */
	SaveableList<Video> filteredVideos; /**< The list of filteredVideo which is needed for the thumbnail generation */
};

#endif  //_THUMBNAILLISTWIDGET_H
