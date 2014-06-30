#if !defined(_OVERLAYCONTROLLER_H)
#define _OVERLAYCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Observer.h"

namespace controller {

/**
*	The OverlayController manages requests to manipulate the list of overlays which can be used for analysing.
**/
class OverlayController : public Observer {
public:
	typedef QScopedPointer<OverlayController> uptr;
	typedef QSharedPointer<OverlayController> sptr;
	typedef QWeakPointer<OverlayController> wptr;

public slots:

	/**
	*	Initiates the insertion of an overlay to the list of overlays which can be used for analysing.
	*	Is called when a notifaction is received that an overlay should be inserted.
	*	@param id The ID of the overlay which is to be inserted.
	**/
	void insertOverlay(QString id);

	/**
	*	Initiates the removal of an overlay from the list of overlays which can be used for analysing.
	*	Is called when a notifaction is received that an overlay should be removed.
	*	@param pos The position of the overlay which is to be removed.
	**/
	void removeOverlay(int pos);
};

}  // namespace controller

#endif  //_OVERLAYCONTROLLER_H
