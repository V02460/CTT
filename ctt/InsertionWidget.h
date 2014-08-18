#ifndef _INSERTIONWIDGET_H
#define _INSERTIONWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QList>
#include <QPushButton>

#include "ViewState.h"
#include "Observer.h"
#include "FilterController.h"
#include "ListedPushButton.h"

namespace view {

/**
 * Based on the current state of the view the insertion widget enables the user to choose the filter or difference to
 * add to the list views.
 */
class InsertionWidget : public QWidget, public::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<InsertionWidget> uptr;
    typedef QSharedPointer<InsertionWidget> sptr;
    typedef QWeakPointer<InsertionWidget> wptr;

	InsertionWidget(QWidget *parent = 0);

	void subscribe(::controller::FilterController controller);

	void unsubscribe(::controller::FilterController controller);

public slots:
    /**
     * Adjusts the InsertionWidget according to the current state of tht whole view.
     * Which means that it creates a button for every filter or difference registered at the corresponding factory (see
     * FilterFactory and DifferenceFactory).
     * So in the processing view only the buttons to add filter are shown while in the analysing view its the buttons to
     * add differences to be shown.
     */
    void changeViewState();

private slots:
	void listedButtonClicked(bool checked, int id);

private:
	void setupUi();

    QList<ListedPushButton::sptr> insertionButtons; /**< The list of buttons to insert filters or differences */
    ViewState *viewState; /**< The current state of the whole GUI */
};

}  // namespace view

#endif  //_INSERTIONWIDGET_H
