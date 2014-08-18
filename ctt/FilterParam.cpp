#include "FilterParam.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

FilterParam::FilterParam(QString name, QVariant value) {
	this->name = name;
	this->value = value;
}

QVariant FilterParam::getValue() const {
	return value;
}

QString FilterParam::getName() const {
	return name;
}

}  // namespace filter
}  // namespace model