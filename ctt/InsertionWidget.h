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

public slots:
    /**
     * Adjusts the InsertionWidget according to the current state of tht whole view.
     * Which means that it creates a button for every filter or difference registered at the corresponding factory (see
     * FilterFactory and DifferenceFactory).
     * So in the processing view only the buttons to add filter are shown while in the analysing view its the buttons to
     * add differences to be shown.
     */
    void changeViewState();

private:
    QList<QPushButton> insertionButtons; /**< The list of buttons to insert filters or differences */
};

}  // namespace view

#endif  //_INSERTIONWIDGET_H
