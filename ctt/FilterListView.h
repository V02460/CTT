


#if !defined(_FILTERLISTVIEW_H)
#define _FILTERLISTVIEW_H

#include "AbstractListView.h"
#include "Filter.h"
#include "FilterParam.h"

class FilterListView : public AbstractListView {
public:
	signal filterMoved(int oldPos, int newPos);
	void filterParamChanged(Filter filter, FilterParam param);
};

#endif  //_FILTERLISTVIEW_H
