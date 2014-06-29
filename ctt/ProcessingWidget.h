


#if !defined(_PROCESSINGWIDGET_H)
#define _PROCESSINGWIDGET_H

#include "Observer.h"
#include "PlayerWidget.h"
#include "Video.h"
#include "ViewType.h"
#include "Player.h"
#include "ThumbnailListWidget.h"
#include "MainControlWidget.h"
#include <QWidget>

/**
 *	The ProcessingWidget basically unites the abilities to  display the video, to control the player and to set the active video pair.
 */
class ProcessingWidget : public Observer , public QWidget {
public slots:
	/**
	*	This method is called when one of the PlayerWidgets managed by this class is set as active.
	*	It emitts the activeVideoChanged signal to all slots connected to this signal
	*
	*	@param playerWidget The playerWidget which was set as active
	*/
	void activatePlayer(PlayerWidget playerWidget);

signals:
	/**
	 *	This signal is emitted when the user changes the active video
	 *
	 *	@param video The video which is set as active
	 */
	void activeVideoChanged(Video video);
	/**
	 *	This signal is emitted when the current view state should be changed
	 *
	 *	@param newView The identifier of the new view state
	 */
	void btnChangeViewClicked(ViewType newView);
private:
	SaveableList<Player> players; /**< The list of players which can be activated */
	QPushButton btnReady; /**< The button to switch from the processing view to the analysing view */
	ThumbnailListWidget thumnailWidget; /**< the list of videos in the current part of the program */
	MainControlWidget mainControlWidget; /**< The MainControlWidget which provides the player functionality */
	QList<PlayerWidget> playerWidgets; /**< The different PlayerWidgets which can be set as active */
};

#endif  //_PROCESSINGWIDGET_H
