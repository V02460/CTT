#ifndef _FILTERPARAMITEM_H
#define _FILTERPARAMITEM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QLabel>

#include "FilterParam.h"

namespace view {
	class FilterParamItem {
	public:
		typedef QScopedPointer<FilterParamItem> uptr;
		typedef QSharedPointer<FilterParamItem> sptr;
		typedef QWeakPointer<FilterParamItem> wptr;

		FilterParamItem(::model::filter::FilterParam::sptr filterParam);
	private:
		QString paramName;

		QLabel *nameLabel;
		union
	};
}

#endif // !_FILTERPARAMITEM_H
