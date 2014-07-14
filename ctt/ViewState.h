#ifndef _VIEWSTATE_H
#define _VIEWSTATE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QObject>
#include <QDir>
#include <QSize>

#include "ViewType.h"
#include "Observable.h"
#include "Saveable.h"
#include "Memento.h"

namespace view {

/**
 * The view state class determines the state the GUI is currently in and notifies all relevant components when the
 * state changes.
 */
class ViewState : public QObject, public model::Observable, public ::model::saveable::Saveable {
    Q_OBJECT
public:
    typedef QScopedPointer<ViewState> uptr;
    typedef QSharedPointer<ViewState> sptr;
    typedef QWeakPointer<ViewState> wptr;

    virtual ::model::saveable::Memento getMemento() const;
    virtual void restore(::model::saveable::Memento memento);
    static ::model::saveable::Saveable::sptr getDummy();


	static ViewState::sptr getInstance();
	/**
	 *	Opens a dialog to configure the ctt's GUI.
	 */
	void openConfigurationDialog();
	/**
	 *	Sets the new main window size.
	 *
	 *	@param newSize The new size of the main window.
	 */
	void setMainWindowSize(QSize newSize);
	/**
	 *	Sets the new selected folder which is needed for the file chooser dialogs.
	 *
	 *	@param newDir The last selected folder.
	 */
	void setLastSelectedFolder(QDir newDir);
	/**
	 *	Returns the current main window size.
	 *
	 *	@return The current mainwindow size.
	 */
	const QSize getMainWindowSize();
	/**
	 *	Returns the last selected folder.
	 *
	 *	@return the last selected folder.
	 */
	const QDir getLastSelectedFolder();

	const ViewType getCurrentViewType();

public slots:
    /**
     * Changes the internal viewType and notifies all Observers about the state change.
     */
    void changeView(ViewType newView);

private:
    ViewType *currentView;
	QSize *currentMainWindowSize;
	QDir *lastSelectedFolder;

	ViewState(); /**< Creates a new ViewState object with default parameters*/

	static ViewState::sptr instance;
};

}  // namespace view

#endif  //_VIEWSTATE_H
