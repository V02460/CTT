#include "FilterParam.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::exception::NotImplementedException;

FilterParam::FilterParam(QString name, QVariant value) {
    throw new NotImplementedException();
}

QVariant FilterParam::getValue() const {
    throw new NotImplementedException();
}

QString FilterParam::getName() const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model