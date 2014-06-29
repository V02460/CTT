#if !defined(_MAINWINDOW_H)
#define _MAINWINDOW_H

#include "Observable.h"
#include "ViewType.h"
#include "ViewState.h"

namespace view {

class MainWindow : public Observable {
public:
	signal menuItemViewStateChanged(ViewType newView);
	slot viewStateChanged();
private:
	ViewState viewState;
	QMenuBar menu;
};

}  // namespace view

#endif  //_MAINWINDOW_H
