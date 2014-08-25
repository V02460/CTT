#ifndef _FILTERLISTVIEWITEM_H
#define _FILTERLISTVIEWITEM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AbstractListViewItem.h"
#include "Filter.h"
#include "FilterController.h"

namespace view {

class FilterListViewItem : public AbstractListViewItem {
public:
	typedef QScopedPointer<FilterListViewItem> uptr;
	typedef QSharedPointer<FilterListViewItem> sptr;
	typedef QWeakPointer<FilterListViewItem> wptr;

	FilterListViewItem(::model::filter::Filter::sptr filter, ::controller::FilterController::sptr filterController);

	virtual QString getIdentifier() Q_DECL_OVERRIDE;
private:
	void setupUi();

	::model::filter::Filter::sptr filter;
};

}

#endif //_FILTERLISTVIEWITEM_H