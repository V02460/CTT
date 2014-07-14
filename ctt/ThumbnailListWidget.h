#ifndef _THUMBNAILLISTWIDGET_H
#define _THUMBNAILLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "Observer.h"
#include "Player.h"
#include "SaveableList.h"

namespace view {
/**
 * The TumbnailListWidget displays a set of videos by its thumbnails and provides the interactable components to set
 * one or more videos active, to add videos to and to remove videos from the program.
 */
class ThumbnailListWidget : public QWidget, public::model::Observer {
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
     */
    ThumbnailListWidget(::model::saveable::SaveableList<::model::player::Player>::sptr players,
                        QWidget *parent = 0);

	void update();

public slots:
	void btnAddVideoClicked();

protected:
	void resizeEvent(QResizeEvent *ev);
signals:
    /**
     * This signal is emitted when a new video is added to the program.
     *
     * @param path The file path that leads to the video file.
     */
    void videoAdded(QFileInfo path);

    /**
     * This signal is emitted when an existing video is removed from the program.
     *
     * @param index The index in the filteredVideos list of the video which should be removed.
     */
    void videoRemoved(int index);
private:
	void setupUi();
	void retranslateUi();
	void resizeButtons();

    QList<QPushButton> *thumbnailList; /**< The list of buttons with the thumbnails of the specific videos as icons */
    QPushButton *btnAddVideo; /**< The button to add a new video */

	QVBoxLayout *verticalLayout;

    /**
     * The list of filteredVideo which is needed for the thumbnail generation.
     */
    ::model::saveable::SaveableList<::model::player::Player>::sptr players;
};

}  // namespace view

#endif  //_THUMBNAILLISTWIDGET_H
