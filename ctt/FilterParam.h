#if !defined(_FILTERPARAM_H)
#define _FILTERPARAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QString>

#include "FilterParam.h"

typedef int any;
// TODO: Get a class

namespace model {
namespace filter {

/**
 * Represents a parameter influencing a Filters behavior.
 */
class FilterParam {
public:
    typedef QScopedPointer<FilterParam> uptr;
    typedef QSharedPointer<FilterParam> sptr;
    typedef QWeakPointer<FilterParam> wptr;

    /**
     * Creates a new FilterParam with the submitted name and value.
     *
     * @param name the name of the parameter
     * @param value value of the parameter
     */
    FilterParam(QString name, any value);

    /**
     * Returns the value of the parameter.
     *
     * @return any the value of the parameter
     */
    any getValue() const;

    /**
     * Returns the name of the parameter.
     *
     * @return any the name of the parameter
     */
    QString getName() const;

    
private:
    QString name; /**<  The name of the parameter. */
};

}  // namespace filter
}  // namespace model

#endif  //_FILTERPARAM_H
