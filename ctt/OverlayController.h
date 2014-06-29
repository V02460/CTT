#if !defined(_OVERLAYCONTROLLER_H)
#define _OVERLAYCONTROLLER_H

#include "Observer.h"

namespace controller {

class OverlayController : public Observer {
public:
	slot insertOverlay(QString id);
	slot removeOverlay(int pos);
};

}  // namespace controller

#endif  //_OVERLAYCONTROLLER_H
