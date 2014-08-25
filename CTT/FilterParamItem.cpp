#include "FilterParamItem.h"

using ::model::filter::FilterParam;

namespace view {
	FilterParamItem::FilterParamItem(FilterParam::sptr param) {
		this->param = param;

		nameLabel = new QLabel(param->getName());

		switch (param->getValue().type()) {
		case QVariant::Bool: initCheckBox(); break;
		case QVariant::Int:
		case QVariant::UInt: initIntSpinbox(); break;
		case QMetaType::Float:
		case QVariant::Double: initDoubleSpinbox(); break;
		default: break;
		}
	}

	void FilterParamItem::initCheckBox() {
		boolCheckbox = new QCheckBox();
		boolCheckbox->setChecked(param->getValue().toBool());
		QObject::connect(boolCheckbox, SIGNAL(stateChanged(int)), this, SLOT(boolStateChanged(int)));
	}

	void FilterParamItem::initIntSpinbox() {
		intSpinbox = new QSpinBox();
		intSpinbox->setMinimum(0);
		intSpinbox->setValue(param->getValue().toInt());
		QObject::connect(intSpinbox, SIGNAL(valueChanged(int)), this, SLOT(intValueChanged(int)));
	}

	void FilterParamItem::initDoubleSpinbox() {
		doubleSpinbox = new QDoubleSpinBox();
		doubleSpinbox->setMinimum(0);
		doubleSpinbox->setValue(param->getValue().toDouble());
		QObject::connect(doubleSpinbox, SIGNAL(valueChanged(double)), this, SLOT(doubleValueChanged(double)));
	}

	QWidget* FilterParamItem::getInteractibleComponent() {
		switch (param->getValue().type()) {
		case QVariant::Bool: return boolCheckbox; break;
		case QVariant::Int:
		case QVariant::UInt: return intSpinbox; break;
		case QMetaType::Float:
		case QVariant::Double: return doubleSpinbox; break;
		default: return 0; break;
		}
	}

	QLabel* FilterParamItem::getNameLabel() {
		return nameLabel;
	}

	void FilterParamItem::boolStateChanged(int newValue) {
		if (!Qt::PartiallyChecked == newValue) {
			if (Qt::Unchecked) {
				param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(false)));
			}
			else if (Qt::Checked) {
				param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(true)));
			}

			emit filterParamChanged(param);
		}
	}

	void FilterParamItem::intValueChanged(int newValue) {
		param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(newValue)));

		emit filterParamChanged(param);
	}

	void FilterParamItem::doubleValueChanged(double newValue) {
		param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(newValue)));

		emit filterParamChanged(param);
	}
}