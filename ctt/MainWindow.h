#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMenuBar>
#include <QMainWindow>

#include "Observable.h"
#include "Observer.h"
#include "ViewType.h"
#include "ViewState.h"
#include "ProcessingWidget.h"
#include "AnalysingWidget.h"

namespace view {
/**
 * The MainWindow unites all intractable components which represent the whole functionality provided by the model.
 */
class MainWindow : public QMainWindow, public::model::Observable, public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<MainWindow> uptr;
    typedef QSharedPointer<MainWindow> sptr;
    typedef QWeakPointer<MainWindow> wptr;

signals:
    /**
     * This signal is emitted when the view state is changed.
     *
     * @param newView The identifier of the view state that should be set as active.
     */
    void menuItemViewStateChanged(ViewType newView);

private:
    ViewState viewState; /**< The current state the whole GUI is in */
    QMenuBar menu; /**< The menu bar which holds all menu items */
    ProcessingWidget processingWidget; /**< The widget to represent the processing view */
    AnalysingWidget analysingWidget; /**< The widget to represent the analyzing view */
};

}  // namespace view

#endif  //_MAINWINDOW_H
