#include "FilterFactory.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::exception::NotImplementedException;

QList<QString> FilterFactory::getAllFilterNotOverlayIDs() {
    throw new NotImplementedException();
}

QList<QString> FilterFactory::getAllFilterIDs() {
    throw new NotImplementedException();
}

Filter::sptr createFilter(QString id) {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model