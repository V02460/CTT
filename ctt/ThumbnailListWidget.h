#ifndef _THUMBNAILLISTWIDGET_H
#define _THUMBNAILLISTWIDGET_H

#include <QScopedPointer>
#include <QWeakPointer>
#include <QLayout>
#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QList>
#include <QDir>

#include "Observer.h"
#include "FilteredVideo.h"
#include "SaveableList.h"
#include "ListedPushButton.h"
#include "VideoListController.h"

namespace view {
/**
 * The TumbnailListWidget displays a set of videos by its thumbnails and provides the interactable components to set
 * one or more videos active, to add videos to and to remove videos from the program.
 */
class ThumbnailListWidget : public QScrollArea, public::model::Observer, public ::model::Observable {
    Q_OBJECT
public:
    typedef QScopedPointer<ThumbnailListWidget> uptr;
    typedef QSharedPointer<ThumbnailListWidget> sptr;
    typedef QWeakPointer<ThumbnailListWidget> wptr;

    /**
     * Creates a new TumbnailListWidget with a SavableList of filteredVideos which is displayed by this widget.
     * The ThumbnailListWidget registers itself at the SaveableList to get notified, when the currently managed videos
     * change.
     *
     * @param filteredVideos The list of videos which should be displayed by this widget.
     * @param selectableCount The number of video which can be activated simultaneously.
	 * @param isHorizontal Defines whether to use a QHBoxLayout (on true) or a QVBoxLayout (on false).
	 * @param parent The parent widget.
     */
    ThumbnailListWidget(::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos,
                        int selectableCount, bool isHorizontal = false, QWidget *parent = 0);

	virtual void update() Q_DECL_OVERRIDE;

	void subscribe(::controller::VideoListController::sptr observer);

	void unsubscribe(const ::controller::VideoListController &observer);
public slots:
	void btnAddVideoClicked(bool checked);
	void listedButtonToggled(bool checked, int id);
signals:
    /**
     * This signal is emitted when a new video is added to the program.
     *
     * @param path The file path that leads to the video file.
     */
    void videoAdded(QString path);

    /**
     * This signal is emitted when an existing video is removed from the program.
     *
     * @param index The index in the filteredVideos list of the video which should be removed.
     */
    void videoRemoved(int index);

	void buttonActivated(int id);
	void buttonReplaced(int oldActiveId, int newActiveId);
	void buttonDeactivated(int id);
private:
    QList<ListedPushButton::sptr> thumbnailList; /**< The list of buttons with the thumbnails of the specific videos as icons */
    QPushButton *btnAddVideo; /**< The button to add a new video */
	QList<int> activatedButtons;
	int selectableCount;
	bool isHorizontal;
	QLayout *thumbnailListLayout;

    /**
     * The list of filteredVideo which is needed for the thumbnail generation.
     */
    ::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;

	void setupUi();
};

}  // namespace view

#endif  //_THUMBNAILLISTWIDGET_H
