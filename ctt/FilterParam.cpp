#include "FilterParam.h"

namespace model {
namespace filter {

FilterParam::FilterParam(QByteArray name, QVariant value) : name(name), value(value) {
}

QVariant FilterParam::getValue() const {
    return value;
}

QByteArray FilterParam::getName() const {
    return name;
}

}  // namespace filter
}  // namespace model