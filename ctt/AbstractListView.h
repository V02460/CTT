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
class AbstractListView : public ::model::Observer, public ::model::Observable, public QTreeWidget {
	Q_OBJECT
public:
    typedef QScopedPointer<AbstractListView> uptr;
    typedef QSharedPointer<AbstractListView> sptr;
    typedef QWeakPointer<AbstractListView> wptr;

signals:
	void elementRemoved(int id);
protected:
	AbstractListView(QWidget *parent = 0);
	void removeAllItems();
	void setupUi();

	QList<AbstractListViewItem::sptr> items;
protected slots:
	void buttonRemoveClicked(bool checked, int id);
private:
    //SaveableList diplayableComponents; /**< The list over the components that should be displayed by the list view */
};

}  // namespace view

#endif  //_ABSTRACTLISTVIEW_H
