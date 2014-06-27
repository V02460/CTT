


#if !defined(_OVERLAYCONTROLLER_H)
#define _OVERLAYCONTROLLER_H

#include "Observer.h"

class OverlayController : public Observer {
public:
	slot insertOverlay(QString id);
	slot removeOverlay(int pos);
};

#endif  //_OVERLAYCONTROLLER_H
