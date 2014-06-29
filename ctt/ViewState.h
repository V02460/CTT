


#if !defined(_VIEWSTATE_H)
#define _VIEWSTATE_H

#include "ViewType.h"
#include "Observable.h"
#include <QObject>

class ViewState : public Observable {
public slots:
	void changeView(ViewType newView);

private:
	ViewType currentView;
};

#endif  //_VIEWSTATE_H
