#ifndef _ABSTRACTLISTVIEW_H
#define _ABSTRACTLISTVIEW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QTreeWidget>

#include "Observer.h"
#include "Observable.h"
#include "AbstractListViewItem.h"
#include "FilteredVideo.h"

namespace view {

/**
 * The AbstracListView is a class to unify all used list view implementations.
 * It stands basically for some kind of list and displays all the elements of that list in a way that is concretized in
 * the specific implementation.
 */
class AbstractListView : public QTreeWidget, public ::model::Observer {
	Q_OBJECT

public:
    typedef QScopedPointer<AbstractListView> uptr;
    typedef QSharedPointer<AbstractListView> sptr;
    typedef QWeakPointer<AbstractListView> wptr;

	virtual void setVideo(::model::filter::FilteredVideo::sptr video);
	virtual void removeVideo();
signals:
	void elementRemoved(int id);

protected:
	AbstractListView(QWidget *parent);
	void setupUi(QList<AbstractListViewItem*> newItems);

	QList<AbstractListViewItem*> items;

protected slots:
	void buttonRemoveClicked(bool checked, int id);
};

}  // namespace view

#endif  //_ABSTRACTLISTVIEW_H
