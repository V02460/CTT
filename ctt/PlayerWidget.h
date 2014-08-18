#ifndef _PLAYERWIDGET_H
#define _PLAYERWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>

#include "VideoProcessingWidget.h"
#include "Player.h"
#include "VideoListController.h"

namespace view {

/**
 * The PlayerWidget holds the VideoWidget displaying the original and the filtered video.
 * The main purpose of this class is to handle the activation of a specific player by the user.
 */
class PlayerWidget : public QWidget{
public:
    typedef QScopedPointer<PlayerWidget> uptr;
    typedef QSharedPointer<PlayerWidget> sptr;
    typedef QWeakPointer<PlayerWidget> wptr;

    /**
     * Creates a PlayerWidget.
     */
    PlayerWidget(model::player::Player::sptr player, ::controller::VideoListController::sptr controller,
		QWidget *parent = 0);

private:
    Q_DISABLE_COPY(PlayerWidget);
	void setupUi();

    VideoProcessingWidget *inputVideo; /**< The original video on which the filters are applied */
    VideoProcessingWidget *filteredVideo;/**< The original video plus the applied filters */
};

}  // namespace view

#endif  //_PLAYERWIDGET_H
