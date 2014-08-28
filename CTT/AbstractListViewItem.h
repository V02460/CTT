#ifndef _ABSTRACTLISTVIEWITEM_H
#define _ABSTRACTLISTVIEWITEM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QTableWidget>

#include "Observer.h"

namespace view {
class AbstractListViewItem : public QTableWidget, public::model::Observer {
public:
	typedef QScopedPointer<AbstractListViewItem> uptr;
	typedef QSharedPointer<AbstractListViewItem> sptr;
	typedef QWeakPointer<AbstractListViewItem> wptr;

	virtual QString getIdentifier() const = 0;
};
}

#endif //_ABSTRACTLISTVIEWITEM_H