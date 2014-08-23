#ifndef _FILTERFACTORY_H
#define _FILTERFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QList>

#include "Filter.h"

namespace model {
namespace filter {

/**
 * Creates Filters and Overlays and provides lists of identifiers of the types of Filters and Overlays it can create.
 *
 */
class FilterFactory {
public:
    typedef QScopedPointer<FilterFactory> uptr;
    typedef QSharedPointer<FilterFactory> sptr;
    typedef QWeakPointer<FilterFactory> wptr;

    /**
     * Returns a list with identifiers for all types of filters which aren't overlays the factory can create.
     *
     * @return QList a list with identifiers for all types of filters which aren't overlays the factory can create
     */
    static QList<QString> getAllNonOverlayFilterIDs();

    /**
    * Returns a list with identifiers for all types of Overlays the factory can create.
    *
    * @return QList a list with identifiers for all types of overlays the factory can create
    */
    static QList<QString> getAllOverlayIDs();

    /**
     * Creates and returns a Filter of the type specified by the submitted id.
     *
     * @return Filter a Filter of the type specified by the submitted id
     * @throws InvalidArgumentException if the submitted id doesn't specify a type of Filter the factory can create.
     */
    static Filter::sptr createFilter(QString id, Module::sptr predecessor);
private:
    FilterFactory() {}
};

}  // namespace filter
}  // namespace model

#endif  //_FILTERFACTORY_H
