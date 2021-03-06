#ifndef _FILTERLISTVIEWITEM_H
#define _FILTERLISTVIEWITEM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AbstractListViewItem.h"
#include "FilterParamItem.h"
#include "Filter.h"
#include "FilterController.h"

namespace view {

class FilterListViewItem : public AbstractListViewItem {
	Q_OBJECT

public:
	typedef QScopedPointer<FilterListViewItem> uptr;
	typedef QSharedPointer<FilterListViewItem> sptr;
	typedef QWeakPointer<FilterListViewItem> wptr;

	FilterListViewItem(::model::filter::Filter::sptr filter,
		               ::controller::FilterController::sptr filterController,
					   QWidget *parent);

	~FilterListViewItem();

	virtual QLabel* getIdentifier() const Q_DECL_OVERRIDE;
	virtual void update() Q_DECL_OVERRIDE;
	virtual bool equals(AbstractListViewItem *other) Q_DECL_OVERRIDE;

public slots:
	void changeFilterParam(::model::filter::FilterParam::sptr newParam);

signals:
	/**
	* This signal is emitted when any filter parameter is changed by the user.
	*
	* @param filter The filter of which the parameter has changed.
	* @param param The parameter that has changed with its new value.
	*/
	void filterParamChanged(const ::model::filter::Filter::sptr filter, ::model::filter::FilterParam::sptr newParam);

private:
	void setupUi();

	::model::filter::Filter::sptr filter;
	QList<FilterParamItem::sptr> filterParams;

	QLabel* identifierLabel;
};

} // namespace view

#endif //_FILTERLISTVIEWITEM_H