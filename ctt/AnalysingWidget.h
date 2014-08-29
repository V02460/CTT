#ifndef _ANALYSINGWIDGET_H
#define _ANALYSINGWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QList>

#include "Player.h"
#include "ThumbnailListWidget.h"
#include "VideoAnalysingWidget.h"
#include "MainControlWidget.h"

namespace view {

/**
 * The AnalysingWidget basically unites the abilities to  display videos and their metadata, to control the player
 * and to set the active videos.
 */
class AnalysingWidget : public QWidget {
public:
    typedef QScopedPointer<AnalysingWidget> uptr;
    typedef QSharedPointer<AnalysingWidget> sptr;
    typedef QWeakPointer<AnalysingWidget> wptr;

	AnalysingWidget(::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos,
		::controller::DifferenceController::sptr differenceCotroller, QWidget *parent = 0);
private:
	void setupUi();

    ::model::player::Player::sptr player; /**< The player which plays all activated videos */
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;
    QList<VideoAnalysingWidget> analysingWidgets; /**< The AnalysingWidgets which actually display videos and their metadata */
    ThumbnailListWidget *thumbnailWidget; /**< The ThumbnalListWidget to choose the active videos and to add new videos */
    MainControlWidget *mainControlWidget;/**< The MainControlWidget which provides the player functionalities */
};

}  // namespace view

#endif  //_ANALYSINGWIDGET_H
