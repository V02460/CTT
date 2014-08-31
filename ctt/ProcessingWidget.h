#ifndef _PROCESSINGWIDGET_H
#define _PROCESSINGWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>

#include "Observer.h"
#include "PlayerWidget.h"
#include "FileVideo.h"
#include "FilteredVideo.h"
#include "ViewType.h"
#include "Player.h"
#include "ThumbnailListWidget.h"
#include "MainControlWidget.h"
#include "SaveableList.h"

namespace view {

/**
 * The ProcessingWidget basically unites the abilities to  display the video, to control the player and to set the
 * active video pair.
 */
class ProcessingWidget : public QWidget, public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<ProcessingWidget> uptr;
    typedef QSharedPointer<ProcessingWidget> sptr;
    typedef QWeakPointer<ProcessingWidget> wptr;

    /**
     * Creates a ProcessingWidget.
     */
	ProcessingWidget(::model::saveable::SaveableList<::model::player::Player>::sptr players,
		::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos,
		::model::saveable::SaveableList<::model::video::FileVideo>::sptr baseVideos, 
		::controller::VideoListController::sptr analysingVideosController, QWidget *parent = 0);

	virtual void update() Q_DECL_OVERRIDE;

public slots:
	void videoActivated(int id);
	void videoReplaced(int oldId, int newId);
	void videoDeactivated(int id);

	void btnChangeViewClicked(bool active);

signals:
    /**
     * This signal is emitted when the current view state should be changed.
     *
     * @param newView The identifier of the new view state.
     */
    void btnChangeViewClicked(ViewType newView);
private:
	void setupUi();

    ::model::saveable::SaveableList<::model::player::Player>::sptr players; /**< The list of players which can be activated */
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;
	::controller::VideoListController::sptr analysingVideosController;
    QPushButton *btnReady; /**< The button to switch from the processing view to the analyzing view */
    ThumbnailListWidget *thumbnailWidget; /**< the list of videos in the current part of the program */
    MainControlWidget *mainControlWidget; /**< The MainControlWidget which provides the player functionality */
    QList<PlayerWidget::sptr> *playerWidgets; /**< The different PlayerWidgets which can be set as active */
	QStackedLayout *playerWidgetsLayout;

	::controller::FilterController::sptr filterController;
};

}  // namespace view

#endif  //_PROCESSINGWIDGET_H
