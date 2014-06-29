#if !defined(_MAINWINDOW_H)
#define _MAINWINDOW_H

#include "Observable.h"
#include "Observer.h"
#include "ViewType.h"
#include "ViewState.h"
#include "ProcessingWidget.h"
#include "AnalysingWidget.h"
#include <QMenuBar>
#include <QMainWindow>

namespace view {
/**
 *	The MainWindow unites all interactable components which represent the whole functionallity provided by the model.
 */
class MainWindow : public Observable , public Observer, public QMainWindow {
signals:
	/**
	 *	This signal is emitted when the view state is changed.
	 *
	 *	@param newView The identifier of the view state that should be set as active.
	 */
	void menuItemViewStateChanged(ViewType newView);
private:
	ViewState viewState; /**< The current state the whole GUI is in */
	QMenuBar menu; /**< The menu bar which holds all menu items */
	ProcessingWidget processingWidget; /**< The widget to represent the processing view */
	AnalysingWidget analysingWidget; /**< The widget to represent the analysing view */
};

}  // namespace view

#endif  //_MAINWINDOW_H
