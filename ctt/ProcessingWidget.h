#ifndef _PROCESSINGWIDGET_H
#define _PROCESSINGWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>

#include "Observer.h"
#include "Video.h"
#include "ViewType.h"
#include "Player.h"
#include "ThumbnailListWidget.h"
#include "SaveableList.h"
#include "Project.h"

#include "PlayerWidget.h"
#include "MainControlWidget.h"
#include "ExtendedTimeline.h"
#include "ThumbnailListWidget.h"

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
	 *
	 * @param project The project wich stores the needed lists
	 * @param parent The parent widget of this widget
     */
	ProcessingWidget(controller::project::Project *project, QWidget *parent = 0);

public slots:
    /**
    * This method is called when one of the PlayerWidgets managed by this class is set as active.
    * It emits the activeVideoChanged signal to all slots connected to this signal.
    *
    * @param playerWidget The playerWidget which was set as active.
    */
    void activatePlayer(const PlayerWidget &playerWidget);

signals:
    /**
     * This signal is emitted when the user changes the active video.
     *
     * @param video The video which is set as active.
     */
    void activeVideoChanged(const ::model::video::Video &video);
    /**
     * This signal is emitted when the current view state should be changed.
     *
     * @param newView The identifier of the new view state.
     */
    void btnChangeViewClicked(ViewType newView);
private:
	void init(controller::project::Project *project);
	void setupUi();
	void retranslateUi();

    ::model::saveable::SaveableList<::model::player::Player>::sptr players; /**< The list of players which can be activated */
	QList<PlayerWidget> *playerWidgets; /**< The different PlayerWidgets which can be set as active */
    QPushButton *switchStateButton; /**< The button to switch from the processing view to the analyzing view */
    ThumbnailListWidget *thumbnailWidget; /**< the list of videos in the current part of the program */
    MainControlWidget *mainControlWidget; /**< The MainControlWidget which provides the player functionality */

	QVBoxLayout *mainVerticalLayout;
	QSplitter *verticalSplitter;
	QWidget *upperWidget;
	QHBoxLayout *upperHorizontalLayout;
	QSplitter *upperHorizontalSplitter;
	QWidget *videoAddWidget;
	QVBoxLayout *thumbnailListVerticalLayout;
	QScrollArea *scrollArea;
	QWidget *scrollAreaThumbnailList;
	QVBoxLayout *scrollAreaVerticalLayout;
	QWidget *switchStateWidget;
	QHBoxLayout *switchStateHoritzontalLayout;
	QSpacerItem *switchStateSpacerleft;
	QSpacerItem *switchStateSpacerRight;
	QFrame *displayFrame;
	QHBoxLayout *displayHorizontalLayout;
	PlayerWidget *displayedPlayerWidget;
	QFrame *controlsFrame;
	QHBoxLayout *controlsHorizontalLayout;
	QSplitter *lowHorizontalSplitter;
	QWidget *lowerLeftWidget;
	QHBoxLayout *mainControlHorizontalLayout;
	QFrame *line;
	QWidget *lowerRightWidget;
	QHBoxLayout *extendedTimelineHorizontalLayout;
	QFrame *line_2;
	ExtendedTimeline *extendedTimeline;
};

}  // namespace view

#endif  //_PROCESSINGWIDGET_H
