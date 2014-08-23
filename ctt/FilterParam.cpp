#include "FilterParam.h"

namespace model {
namespace filter {

FilterParam::FilterParam(QString name, QVariant value) : name(name), value(value) {
}

QVariant FilterParam::getValue() const {
    return value;
}

QString FilterParam::getName() const {
    return name;
}

}  // namespace filter
}  // namespace model