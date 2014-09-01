#ifndef _MAINCONTROLWIDGET_H
#define _MAINCONTROLWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QStackedLayout>

#include "Observer.h"
#include "AbstractListView.h"
#include "InsertionWidget.h"
#include "ZoomFunctions.h"
#include "PlayerFunctions.h"
#include "FrameDiff.h"
#include "FilterController.h"
#include "DifferenceController.h"
#include "AnalysingOrderingWidget.h"
#include "AbstractTimeline.h"
#include "ViewType.h"

namespace view {

/**
 * The MainControlWidget holds all components used for video playback, filter/ difference insertion and changing.
 */
class MainControlWidget : public QWidget, public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<MainControlWidget> uptr;
    typedef QSharedPointer<MainControlWidget> sptr;
    typedef QWeakPointer<MainControlWidget> wptr;

	MainControlWidget(::controller::FilterController::sptr filterController, QWidget *parent = 0);

	MainControlWidget(::model::saveable::SaveableList<::model::difference::FrameDiff>::sptr differences,
		::model::player::Player::sptr player, AnalysingOrderingWidget::sptr orderingWidget, QWidget *parent = 0);

	void setPlayer(::model::player::Player::sptr player);
	void setVideo(::model::filter::FilteredVideo::sptr video);
	void removePlayer();
	void removeVideo();

	virtual void update();

public slots:
    /**
     * Hides the timeline widget and shows the insertion widget, as long as the button is active.
     * Does the opposite as soon as the button is inactive.
     *
     * @param active Is true, when btnInsert is active, and false otherwise.
     */
    void btnInsertClicked(bool active);

private:

	void setupUi(ViewType viewType);

    QPushButton *btnInsert; /**< The toggle button that indicates whether insertion mode is active or not */
    AbstractTimeline *timeline; /**< The timeline showing the currently relevant information */
    InsertionWidget *insertionWidget; /**< The InsertionWidget to insert filters or differences */
    ZoomFunctions *zoomBar; /**< The zoom funtionality */
    PlayerFunctions *playerFunctions; /** The funtionality to control the video player */
    AbstractListView *listView; /** The list view to show the current active differences or filters (depends on the viewState) */

	QStackedLayout *rightDisplayWidgetLayout;
};

}  // namespace view

#endif  //_MAINCONTROLWIDGET_H
