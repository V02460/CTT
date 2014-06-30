#if !defined(_FILTERFACTORY_H)
#define _FILTERFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QList>

#include "Filter.h"

namespace model {
namespace filter {

class FilterFactory {
public:
	typedef QScopedPointer<FilterFactory> uptr;
	typedef QSharedPointer<FilterFactory> sptr;
	typedef QWeakPointer<FilterFactory> wptr;

	static QList<QString> getAllFilterIDs();
	static Filter::sptr createFilter(QString id);
private:
	FilterFactory() {}
};

}  // namespace filter
}  // namespace model

#endif  //_FILTERFACTORY_H
