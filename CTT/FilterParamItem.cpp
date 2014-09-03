#include "FilterParamItem.h"

#include "IllegalArgumentException.h"

using ::model::filter::FilterParam;
using ::exception::IllegalArgumentException;

namespace view {

	FilterParamItem::FilterParamItem(FilterParam::sptr param) : param(param),
		                                                        nameLabel(param->getName()),
																boolCheckbox(),
																intSpinbox(),
																doubleSpinbox() {
	switch (param->getValue().type()) {
	case QVariant::Bool: initCheckBox(); break;
	case QVariant::Int:
	case QVariant::UInt: initIntSpinbox(); break;
	case QMetaType::Float:
	case QVariant::Double: initDoubleSpinbox(); break;
	default:
		throw IllegalArgumentException("There are only bool, integer, unsigned integer, float and double params.");
		break;
	}
}

void FilterParamItem::initCheckBox() {
	boolCheckbox.setChecked(param->getValue().toBool());
	QObject::connect(&boolCheckbox, SIGNAL(stateChanged(int)), this, SLOT(boolStateChanged(int)));
}

void FilterParamItem::initIntSpinbox() {
	intSpinbox.setMinimum(0);
	intSpinbox.setValue(param->getValue().toInt());
	QObject::connect(&intSpinbox, SIGNAL(valueChanged(int)), this, SLOT(intValueChanged(int)));
}

void FilterParamItem::initDoubleSpinbox() {
	doubleSpinbox.setMinimum(0);
	doubleSpinbox.setValue(param->getValue().toDouble());
	doubleSpinbox.setSingleStep(0.25);
	QObject::connect(&doubleSpinbox, SIGNAL(valueChanged(double)), this, SLOT(doubleValueChanged(double)));
}

QWidget* FilterParamItem::getInteractibleComponent() {
	switch (param->getValue().type()) {
	case QVariant::Bool: return &boolCheckbox; break;
	case QVariant::Int:
	case QVariant::UInt: return &intSpinbox; break;
	case QMetaType::Float:
	case QVariant::Double: return &doubleSpinbox; break;
	default:
		throw IllegalArgumentException("There are only bool, integer, unsigned integer, float and double params.");
		break;
	}
}

QLabel* FilterParamItem::getNameLabel() {
	return &nameLabel;
}

void FilterParamItem::boolStateChanged(int newValue) {
	if (!Qt::PartiallyChecked == newValue) {
		if (Qt::Unchecked) {
			param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(false)));
		} else if (Qt::Checked) {
			param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(true)));
		}

		emit filterParamChanged(param);
	}
}

void FilterParamItem::intValueChanged(int newValue) {
	if (param->getValue().type() == QVariant::Int) {
		param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(newValue)));
	} else {
		if (newValue < 0) {
			newValue = 0;
		}

		param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(static_cast<unsigned int>(newValue))));
	}

	emit filterParamChanged(param);
}

void FilterParamItem::doubleValueChanged(double newValue) {
	if (param->getValue().type() == QVariant::Double) {
		param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(newValue)));
	} else {
		param = FilterParam::sptr(new FilterParam(param->getName(), QVariant(static_cast<float>(newValue))));
	}

	emit filterParamChanged(param);
}

} // namespace view