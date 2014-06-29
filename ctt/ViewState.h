#if !defined(_VIEWSTATE_H)
#define _VIEWSTATE_H

#include "ViewType.h"
#include "Observable.h"
#include <QObject>

namespace view {

/**
 *	The view state class determines the state the GUI is currently in and notifies all relevant components when the state changes.
 */
class ViewState : public Observable {
public slots:
	/**
	 * Changes the internal viewType and notifies all Observers about the state change.
	 */
	void changeView(ViewType newView);

private:
	ViewType currentView;
};

}  // namespace view

#endif  //_VIEWSTATE_H
