#if !defined(_FILTERPARAM_H)
#define _FILTERPARAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QString>

#include "FilterParam.h"

class any; // TODO: Get a class

namespace model {
namespace filter {

class FilterParam {
public:
	typedef QScopedPointer<FilterParam> uptr;
	typedef QSharedPointer<FilterParam> sptr;
	typedef QWeakPointer<FilterParam> wptr;

	void FilterParam(QString name);

	any getValue() const;
	void setValue(any value);
	
private:
	QString name;
};

}  // namespace filter
}  // namespace model

#endif  //_FILTERPARAM_H
