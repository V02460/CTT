#ifndef _FILTERLISTVIEWELEMENT_H
#define _FILTERLISTVIEWELEMENT_H

#include <QTableWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include "Filter.h"
#include "FilterController.h"
#include "Observer.h"

namespace view {
class FilterListViewElement : public ::model::Observer, public QTableWidget {
public:
	typedef QScopedPointer<FilterListViewElement> uptr;
	typedef QSharedPointer<FilterListViewElement> sptr;
	typedef QWeakPointer<FilterListViewElement> wptr;

	FilterListViewElement(model::filter::Filter::sptr filter, controller::FilterController::sptr controller,
		QWidget *parent = 0);

	QString getFilterName();
		
	virtual void update() Q_DECL_OVERRIDE;
signals:
	void changeFilterParam(const ::model::filter::Filter &filter, ::model::filter::FilterParam param);
private:
	void setupUi();

	model::filter::Filter::sptr filter;

	QList<QSharedPointer<QCheckBox>> *checkboxes;
	QList<QSharedPointer<QSpinBox>> *intSpinboxes;
	QList<QSharedPointer<QDoubleSpinBox>> *doubleSpinboxes;
	QList<QSharedPointer<QLineEdit>> *texts;

private slots:
	void changed();
};

} //namespace view

#endif //_FILTERLISTVIEWELEMENT_H