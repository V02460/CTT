#ifndef _ABSTRACTLISTVIEWITEM_H
#define _ABSTRACTLISTVIEWITEM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QTableWidget>
#include <QLabel>

#include "Observer.h"

namespace view {

class AbstractListViewItem : public QTableWidget, public::model::Observer {

public:
	typedef QScopedPointer<AbstractListViewItem> uptr;
	typedef QSharedPointer<AbstractListViewItem> sptr;
	typedef QWeakPointer<AbstractListViewItem> wptr;

	AbstractListViewItem(QWidget *parent);

	virtual QLabel* getIdentifier() const = 0;

	const int getHeight();

	virtual bool equals(AbstractListViewItem *other) = 0;

protected:
	void setHeight(int height);

private:
	void setupUi();

	int forcedHeight;
};

}  // namespace view

#endif //_ABSTRACTLISTVIEWITEM_H