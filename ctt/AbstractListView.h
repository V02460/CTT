#ifndef _ABSTRACTLISTVIEW_H
#define _ABSTRACTLISTVIEW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QTreeWidget>

#include "Observer.h"
#include "Observable.h"
#include "AbstractListViewItem.h"

namespace view {

/**
 * The AbstracListView is a class to unify all used list view implementations.
 * It stands basically for some kind of list and displays all the elements of that list in a way that is concretized in
 * the specific implementation.
 */
class AbstractListView : public QTreeWidget, public ::model::Observer, public ::model::Observable {
	Q_OBJECT

public:
    typedef QScopedPointer<AbstractListView> uptr;
    typedef QSharedPointer<AbstractListView> sptr;
    typedef QWeakPointer<AbstractListView> wptr;

signals:
	void elementRemoved(int id);

protected:
	AbstractListView(QWidget *parent);
	void removeAllItems();
	void setupUi();

	QList<AbstractListViewItem*> items;

protected slots:
	void buttonRemoveClicked(bool checked, int id);
};

}  // namespace view

#endif  //_ABSTRACTLISTVIEW_H
