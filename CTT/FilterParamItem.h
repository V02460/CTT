#ifndef _FILTERPARAMITEM_H
#define _FILTERPARAMITEM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QLabel>
#include <QSpinBox>
#include <QCheckbox>
#include <QDoubleSpinBox>

#include "FilterParam.h"

namespace view {
class FilterParamItem : public QObject {
	Q_OBJECT
public:
	typedef QScopedPointer<FilterParamItem> uptr;
	typedef QSharedPointer<FilterParamItem> sptr;
	typedef QWeakPointer<FilterParamItem> wptr;

	FilterParamItem(::model::filter::FilterParam::sptr filterParam);

	QLabel* getNameLabel();
	QWidget* getInteractibleComponent();
public slots:
	void doubleValueChanged(double newValue);
	void intValueChanged(int newValue);
	void boolStateChanged(int newState);
signals:
	void filterParamChanged(::model::filter::FilterParam::sptr newFilterParam);
private:
	void initCheckBox();
	void initIntSpinbox();
	void initDoubleSpinbox();

	::model::filter::FilterParam::sptr param;

	QLabel *nameLabel;
	QCheckBox *boolCheckbox;
	QSpinBox *intSpinbox;
	QDoubleSpinBox *doubleSpinbox;
};
}

#endif // !_FILTERPARAMITEM_H
