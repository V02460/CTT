#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMenuBar>
#include <QMainWindow>
#include <QStackedLayout>
#include <QAction>

#include "Observable.h"
#include "Observer.h"
#include "ViewType.h"

#include "ViewState.h"
#include "ProcessingWidget.h"
#include "AnalysingWidget.h"
#include "MainController.h"

namespace view {
/**
 * The MainWindow unites all intractable components which represent the whole functionality provided by the model.
 */
class MainWindow : public QMainWindow, public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<MainWindow> uptr;
    typedef QSharedPointer<MainWindow> sptr;
    typedef QWeakPointer<MainWindow> wptr;

	MainWindow();

	virtual void update() Q_DECL_OVERRIDE;

public slots:
	void menuToProcessing();
	void menuToAnalysing();

	void menuLoad();
	void menuSave();
signals:
    /**
     * This signal is emitted when the view state is changed.
     *
     * @param newView The identifier of the view state that should be set as active.
     */
    void menuItemViewStateChanged(ViewType newView);

	void loadProject(QString path);
	void saveProjectAs(QString path, ::controller::project::SaveFileType type);

private:
	void setupUi();

    QMenuBar *menu; /**< The menu bar which holds all menu items */
	QAction *toProcessingView;
	QAction *toAnalysingView;
	QStackedLayout *centralWidgetLayout;

	::controller::MainController::sptr mainController;
};

}  // namespace view

#endif  //_MAINWINDOW_H
