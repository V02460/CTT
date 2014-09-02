#ifndef _FILTERFACTORY_H
#define _FILTERFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QList>

#include "PixelDiff.h"
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
    static QList<QByteArray> getAllNonOverlayFilterIDs();

    /**
    * Returns a list with identifiers for all types of Overlays the factory can create.
    *
    * @return QList a list with identifiers for all types of overlays the factory can create
    */
    static QList<QByteArray> getAllOverlayIDs();

    /**
     * Creates and returns a Filter of the type specified by the submitted id.
     * @param id The id of the Filter to create
     * @param predecessor The predecessor of the created Filter
     *
     * @return Filter a Filter of the type specified by the submitted id
     * @throws InvalidArgumentException if the submitted id doesn't specify a type of Filter the factory can create.
     */
    static Filter::sptr createFilter(QString id, Module::sptr predecessor);

    /**
    * Creates and returns a Filter of the type specified by the submitted id.
    * @param id The id of the Filter to create
    * @param predecessor The predecessor of the created Filter
    * @param pixelDiff Some filters need a PixelDiff to work. In this case this parameter must be provided.
    *
    * @return Filter a Filter of the type specified by the submitted id
    * @throws InvalidArgumentException if the submitted id doesn't specify a type of Filter the factory can create.
    */
    static Filter::sptr createFilter(QString id, Module::sptr predecessor, ::model::difference::PixelDiff::sptr pixelDiff);
private:
    Q_DISABLE_COPY(FilterFactory);

    FilterFactory() {}
};

}  // namespace filter
}  // namespace model

#endif  //_FILTERFACTORY_H
