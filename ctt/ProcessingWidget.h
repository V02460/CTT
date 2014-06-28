


#if !defined(_PROCESSINGWIDGET_H)
#define _PROCESSINGWIDGET_H

#include "Observer.h"
#include "PlayerWidget.h"
#include "Video.h"
#include "ViewType.h"

class ProcessingWidget : public Observer {
public:
	QPushButton btnReady;
	slot activatePlayer(PlayerWidget playerWidget);
	signal activeVideoChanged(Video video);
	signal btnChangeViewClicked(ViewType newView);
private:
	SaveableList<Player> players;
};

#endif  //_PROCESSINGWIDGET_H
