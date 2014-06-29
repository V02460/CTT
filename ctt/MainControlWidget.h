#if !defined(_MAINCONTROLWIDGET_H)
#define _MAINCONTROLWIDGET_H

#include "Observer.h"
#include "ExtendedTimeline.h"
#include "AbstractListView.h"
#include "InsertionWidget.h"
#include "ZoomFunctions.h"
#include "PlayerFunctions.h"

namespace view {

/**
 *	The MainControlWidget holds all components used for video playback, filer/ difference insertion and changing.
 */
class MainControlWidget : public Observer, public QWidget {
public slots:
	/**
	 *	Hides the ExtendedTimeline widget and shows the insertion widget, as long as the button is active.
	 *	Does the opposite as soon as the button is inactive
	 *
	 *	@param active Is true, when btnInsert is active, and false otherwise
	 */
	void btnInsertClicked(bool active);

	/**
	 * Adjusts the MainControlWidget to the state of the whole GUI.
	 * Which means that the listView is changed to a list view of another type (Filter to Difference or vice versa)
	 */
	void changeViewState();

private:
	QPushButton btnInsert; /**< The toggle button that indicates wether insertion mode is active or not */
	ViewState viewState; /**< The current state of the whole GUI */
	ExtendedTimeline timeline; /**< The ExtendedTimeline showing the currently relevant information */
	InsertionWidget insertionWidget; /**< The InsertionWidget to insert filters or differences */
	ZoomFunctions zoomBar; /**< The zoom funtionality */
	PlayerFunctions playerFunctions; /** The funtionality to control the video player */
	AbstractListView listView; /** The list view to show the current active differences or filters (depends on the viewState) */
};

}  // namespace view

#endif  //_MAINCONTROLWIDGET_H
