


#if !defined(_PLAYERWIDGET_H)
#define _PLAYERWIDGET_H

#include "VideoProcessingWidget.h"
#include <QObject>

/**
 *	The PlayerWidget holds the VideoWidget displaying the original and the filtered video.
 *	The main purpose of this class is to handle the activation of a specific player by the user.
 */
class PlayerWidget {
public slots:
	/**
	 *	Recieves the activation signal form a button in the ThumbnailListWidget and notifies the ProcessingWidget about the activation
	 *	by emitting the playerActivated signal.
	 */
	void getActivationSignal();

signals:
	/**
	 *	This signal is emitted as soon as this PlayerWidget gets activated.
	 *
	 *	@param playerWidget The concrete playerWidget which was activated.
	 */
	void playerActivated(PlayerWidget playerWidget);

private:
	VideoProcessingWidget inputVideo; /**< The original video on which the filters are apllied */
	VideoProcessingWidget filteredVideo;/**< The original video plus the applied filters */
};

#endif  //_PLAYERWIDGET_H
