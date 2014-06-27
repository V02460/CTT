


#if !defined(_VIEWSTATE_H)
#define _VIEWSTATE_H

#include "ViewType.h"

class ViewState {
public:
	signal currentViewChanged();
	slot changeView(ViewType newView);
private:
	ViewType currentView;
};

#endif  //_VIEWSTATE_H
